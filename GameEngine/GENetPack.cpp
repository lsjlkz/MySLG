//
// Created by lsjlkz on 2022/6/15.
//

#include "GENetPack.h"



PackMessage::PackMessage() {
	this->MsgSize = 0;
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

bool PackMessage::PackBigObj(BigObj bigObj) {
	// 打包类型
	this->PackInt(ISBIGOBJ);
	PackMessage* packObj = new PackMessage();
	packObj->PackBigObj(bigObj);
	// 打包长度
	// TODO
	return true;
}

bool PackMessage::PackInt(int i) {
	this->PackByte(&i, sizeof(int));
	return true;
}

bool PackMessage::PackIntObj(int i) {
	this->PackInt(ISINT);
	this->PackInt(i);
	return true;
}

bool PackMessage::PackLong(long l) {
	this->PackByte(&l, sizeof(long));
	return true;
}

bool PackMessage::PackLongObj(long l) {
	this->PackInt(ISLONG);
	this->PackLong(l);
	return true;
}

bool PackMessage::PackBool(bool b) {
	this->PackByte(&b, sizeof(bool));
	return true;
}

bool PackMessage::PackBoolObj(bool b) {
	this->PackInt(ISBOOL);
	this->PackInt(b);
	return true;
}

bool PackMessage::PackFloat(float f) {
	this->PackByte(&f, sizeof(float));
	return true;
}

bool PackMessage::PackFloatObj(float f) {
	this->PackInt(ISFLOAT);
	this->PackFloat(f);
	return true;
}

bool PackMessage::PackDouble(double d) {
	this->PackByte(&d, sizeof(double));
	return true;
}

bool PackMessage::PackDoubleObj(double d) {
	this->PackInt(ISDOUBLE);
	this->PackDouble(d);
	return true;
}

bool PackMessage::PackString(char *s, int size) {
	this->PackByte(s, size);
	return true;
}

bool PackMessage::PackStringObj(char *s, int size) {
	this->PackInt(ISSTRING);
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