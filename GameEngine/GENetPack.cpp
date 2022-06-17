//
// Created by lsjlkz on 2022/6/15.
//

#include "GENetPack.h"



PackMessage::PackMessage() {
	this->MsgSize = 0;
	this->NewBuf();
}

PackMessage::~PackMessage() {
	bigMsgQueue->clear();
	bigMsgPool->clear();
}

void PackMessage::NewBuf() {
	if(this->bigMsgPool == nullptr){
		curBufHead = new char[MSG_MAX_SIZE];
		return;
	}
	if(this->bigMsgPool->empty()){
		curBufHead = new char[MSG_MAX_SIZE];
		return;
	}
	curBufHead = this->bigMsgPool->back();
	this->bigMsgQueue->push_back(curBufHead);
	this->bigMsgPool->pop_back();
	this->curBufOffset = 0;
	this->curBufEmpty = MSG_MAX_SIZE;
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

bool PackMessage::PackFloat(float f) {
	this->PackByte(&f, sizeof(float));
	return true;
}

bool PackMessage::PackFloatObj(float f) {
	this->PackType(FloatFlag);
	this->PackFloat(f);
	return true;
}

bool PackMessage::PackDouble(double d) {
	this->PackByte(&d, sizeof(double));
	return true;
}

bool PackMessage::PackDoubleObj(double d) {
	this->PackType(DoubleFlag);
	this->PackDouble(d);
	return true;
}

bool PackMessage::PackString(const char *s, int size) {
	this->PackByte(s, size);
	return true;
}

bool PackMessage::PackStringObj(const char *s, int size) {
	this->PackType(StringFlag);
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
		this->MsgSize += size;
		this->curBufEmpty -= size;
		return;
	}
	char* curP = (char *) pHead;
	// 不够用了，重新申请一个
	while(size > MSG_MAX_SIZE){
		// 放入空余的位置
		memcpy(this->curBufHead, curP, this->curBufEmpty);
		curP += this->curBufEmpty;
		this->MsgSize += this->curBufEmpty;
		size -= this->curBufEmpty;
		this->NewBuf();
	}
	memcpy(this->curBufHead, pHead, size);
	this->curBufOffset += size;
	this->MsgSize += size;
	this->curBufEmpty -= size;
}

bool PackMessage::PackLuaObj(lua_State *L) {
	return false;
}

bool PackMessage::PackLuaHelp(lua_State *L, int index) {
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
		int i = lua_tonumber(L, index);
		this->PackIntObj(i);
	}else if(lt == LUA_TSTRING){
		size_t size = 0;
		const char* s = lua_tolstring(L, index, &size);
		this->PackStringObj(s, size);
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
		}
	}
	return false;
}

int &PackMessage::PackIntRef() {
	int*r = new int(0);
	this->PackInt(*r);
	return *r;
}

