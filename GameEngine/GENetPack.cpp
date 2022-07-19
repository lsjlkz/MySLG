//
// Created by lsjlkz on 2022/6/15.
//

#include "GENetPack.h"


PackMessage::PackMessage() {
	bigMsgPool = new BufPool();
	bigMsgQueue = new BufQueue();
	this->msgSize = 0;
	this->NewBuf();
}

PackMessage::~PackMessage() {
	bigMsgPool->clear();
	bigMsgQueue->clear();
}

void PackMessage::NewBuf() {
	if(bigMsgPool->empty()){
		curBufHead = new char[MSG_MAX_SIZE];
	}else{
		curBufHead = bigMsgPool->back();
		bigMsgPool->pop_back();
	}
	this->bigMsgQueue->push_back(curBufHead);
	this->curBufOffset = 0;
	this->curBufEmpty = MSG_MAX_SIZE;
}

char* PackMessage::MsgIter(){
	for(auto & it : *bigMsgQueue){
		return it;
	}
}

bool PackMessage::PackType(int t) {
	this->PackCharInt(t);
	return false;
}

bool PackMessage::PackCharInt(int c) {
	char cc = static_cast<char>(c);
	this->PackChar(cc);
	return true;
}

bool PackMessage::PackChar(char c) {
	this->PackByte(&c, sizeof(char));
	return true;
}

bool PackMessage::PackInt(int i) {
	this->PackByte(&i, sizeof(int));
	return true;
}

bool PackMessage::PackIntObj(int i) {
	this->PackType(IntFlag);
	this->PackInt(i);
	return true;
}

bool PackMessage::PackLong(long l) {
	this->PackByte(&l, sizeof(long));
	return true;
}

bool PackMessage::PackLongObj(long l) {
	this->PackType(LongFlag);
	this->PackLong(l);
	return true;
}

bool PackMessage::PackBool(bool b) {
	if(b){
		char bb = static_cast<char>(TrueFlag);
	}else{
		char bb = static_cast<char>(FalseFlag);
	}
	this->PackByte(new char(FalseFlag), sizeof(char));
	return true;
}

bool PackMessage::PackBoolObj(bool b) {
	this->PackType(BoolFlag);
	this->PackInt(b);
	return true;
}

bool PackMessage::PackString(const char *s, int size) {
	this->PackByte(s, size);
	return true;
}

bool PackMessage::PackStringObj(const char *s, int size) {
	this->PackType(StringFlag);
	this->PackInt(size);
	this->PackString(s, size);
	return true;
}


void PackMessage::PackByte(const void *pHead, int size) {
	if(this->curBufEmpty == 0){
		// 无空间了，重新申请一个
		this->NewBuf();
	}
	if(size <= this->curBufEmpty){
		// 还够用，不用重新申请
		memcpy(this->curBufHead, pHead, size);
		this->curBufOffset += size;
		this->msgSize += size;
		this->curBufEmpty -= size;
		return;
	}
	char* curP = (char *) pHead;
	// 不够用了，重新申请一个
	while(size > MSG_MAX_SIZE){
		// 放入空余的位置
		memcpy(this->curBufHead, curP, this->curBufEmpty);
		curP += this->curBufEmpty;
		this->msgSize += this->curBufEmpty;
		size -= this->curBufEmpty;
		this->NewBuf();
	}
	memcpy(this->curBufHead, pHead, size);
	this->curBufOffset += size;
	this->msgSize += size;
	this->curBufEmpty -= size;
}

bool PackMessage::PackLuaObj(lua_State *L) {
	if(this->bigMsgQueue == NULL){
		return false;
	}
	int top = lua_gettop(L);
	if(top <= 0){
		std::cout << "lua object empty" << std::endl;
		return false;
	}
	int& size = this->PackIntRef();
	this->curStackDeep = 0;
	int msg_type = (int) lua_tointeger(L, -2);
	this->PackIntObj(msg_type);
	this->PackLuaHelp(L, -1);
	size = this->PackSize();
	return true;
}

void PackMessage::PackLuaHelp(lua_State *L, int index) {
	this->curStackDeep++;		// 增加递归深度
	int top = lua_gettop(L);
	int lt = lua_type(L, index);
	if(lt == LUA_TNIL){
		// nil
		this->PackType(NoneFlag);
	}else if(lt == LUA_TBOOLEAN){
		// bool
		int b = lua_toboolean(L, index);
		if(b){
			this->PackType(TrueFlag);
		}else{
			this->PackType(FalseFlag);
		}
	}else if(lt == LUA_TNUMBER){
		int i = lua_tointeger(L, index);
		this->PackIntObj(i);
	}else if(lt == LUA_TSTRING){
		size_t size = 0;
		const char* s = lua_tolstring(L, index, &size);
		// TODO 越界
		this->PackStringObj(s, (int)size);
	}else if(lt == LUA_TTABLE){
		int& TableSize = this->PackIntRef();
		int size = 0;
		// 也就是把-1这些索引转为正值的索引，如长度为n，索引-2应为倒数第二个，也就是转为n-1
		int table_index = lua_absindex(L, index);
		// lua_checkstack检测栈上是否有足够的空间，如下是检测top上是否还有2个位置，不够的话会自动扩容
		lua_checkstack(L, top + 2);
		lua_pushnil(L);
		ASSERT_LUA_TOP(L, top, 1);
		while(lua_next(L, table_index)){
			ASSERT_LUA_TOP(L, top, 2);
			size++;
			int ud = this->curStackDeep;
			this->PackLuaHelp(L, -2);
			GE_WIN_ASSERT(ud == this->curStackDeep);
			ASSERT_LUA_TOP(L, top, 2);

			this->PackLuaHelp(L, -1);
			ASSERT_LUA_TOP(L, top, 2);

			lua_pop(L, 1);
			ASSERT_LUA_TOP(L, top, 1);
		}

		ASSERT_LUA_TOP(L, top, 0);
		TableSize = size;
	}else{
		std::cout << "not support lua object" << std::endl;
	}
	ASSERT_LUA_TOP(L, top, 0);
	--(this->curStackDeep);
}

int &PackMessage::PackIntRef() {
	int*r = new int(0);
	// 把长度打包进去，最后再改
	this->PackByte(r, sizeof(int));
	return *r;
}

void PackMessage::ClearCache() {
	while(!this->bigMsgQueue->empty()){
		bigMsgPool->push_back(this->bigMsgQueue->back());
		this->bigMsgQueue->pop_back();
	}
}

bool UnpackMessage::UnpackType(int &flag) {
	if(leftSize < sizeof(int)){
		this->isOK = false;
		return false;
	}
	flag = static_cast<int>(*(curBufHead));
	curBufHead += sizeof(int);
	leftSize -= sizeof(int);
	return true;
}

bool UnpackMessage::UnpackInt(int& i) {
	if(leftSize < sizeof(int)){
		this->isOK = false;
		return false;
	}
	i = static_cast<int>(*(curBufHead));
	curBufHead += sizeof(int);
	leftSize -= sizeof(int);
	return true;
}

bool UnpackMessage::UnpackLong(long &l) {
	if(leftSize < sizeof(long)){
		this->isOK = false;
		return false;
	}
	l = static_cast<long>(*(curBufHead));
	curBufHead += sizeof(long);
	leftSize -= sizeof(long);
	return true;
}

bool UnpackMessage::UnpackBool(bool &b) {
	if(leftSize < sizeof(bool)){
		this->isOK = false;
		return false;
	}
	b = static_cast<bool>(*(curBufHead));
	curBufHead += sizeof(bool);
	leftSize -= sizeof(bool);
	return true;
}

bool UnpackMessage::UnpackString(char *s, int size) {
	if(leftSize < size){
		this->isOK = false;
		return false;
	}
	memcpy(s, curBufHead, size);
	curBufHead += size;
	return true;
}

UnpackMessage::UnpackMessage(void *pHead){
	msgSize = 0;
	leftSize = 0;
	curBufHead = reinterpret_cast<char*>(pHead);
	curBufOffset = 0;
}

UnpackMessage::UnpackMessage(void *pHead, int nSize) {
	msgSize = nSize;
	leftSize = msgSize;
	curBufHead = reinterpret_cast<char*>(pHead);
	curBufOffset = 0;
}

bool UnpackMessage::UnpackLuaObj(lua_State *L) {
	int top = lua_gettop(L);
	this->UnpackLuaObjHelp(L);

	ASSERT_LUA_TOP(L, top, 1);
	return this->isOK;
}

bool UnpackMessage::UnpackLuaObjHelp(lua_State *L) {
	if(!this->isOK){
		lua_pushnil(L);
		return false;
	}

	int top = lua_gettop(L);
	lua_checkstack(L, top + 5);
	int flag = 0;
	this->UnpackType(flag);
	switch(flag){
		case IntFlag:
		{
			int i = 0;
			if(this->UnpackInt(i)){ lua_pushinteger(L, i); }
			else{ lua_pushinteger(L, 0); }
			break;
		}
		case LongFlag:
		{

			long l = 0;
			if(this->UnpackLong(l)){ lua_pushinteger(L, l); }
			else{ lua_pushinteger(L, 0); }
			break;
		}
		case StringFlag:
		{
			int s = 0;
			this->UnpackInt(s);
			char* str = new char(s);
			if(this->UnpackString(str, s)) { lua_pushlstring(L, str, s); }
			else { lua_pushnil(L); }
			break;
		}
		case NoneFlag:
		{
			lua_pushnil(L);
			break;
		}
		case TrueFlag:
		{
			lua_pushboolean(L, 1);
			break;
		}
		case FalseFlag:
		{
			lua_pushboolean(L, 0);
			break;
		}
		case TableFlag:
		{
			int size = 0;
			// table的长度
			this->UnpackInt(size);
			lua_createtable(L, size, 0);
			ASSERT_LUA_TOP(L, top, 1);
			int table_index = lua_gettop(L);
			for(int idx = 0; idx < size; idx++){
				lua_pushinteger(L, idx + 1);
				ASSERT_LUA_TOP(L, top, 2);
				this->UnpackLuaObjHelp(L);
				ASSERT_LUA_TOP(L, top, 3);
				lua_settable(L, table_index);
				ASSERT_LUA_TOP(L, top, 1);
			}
			break;
		}
		default:
		{
			lua_pushnil(L);
			break;
		}
	}
	ASSERT_LUA_TOP(L, top, 1);
	return true;
}
