//
// Created by lsjlkz on 2022/6/15.
//

#ifndef MYSLG_GENETPACK_H
#define MYSLG_GENETPACK_H

#include <vector>
#include <list>

#define ISINT -1
#define ISLONG -2
#define ISBOOL -3
#define ISFLOAT -4
#define ISDOUBLE -5
#define ISBIGOBJ -6
#define ISSTRING -7

#define MSG_MAX_SIZE 65536

typedef std::vector<char*>			BufPool;
typedef std::list<char*>			BufQueue;

// 这个模块即将会很庞大，貌似

class BigObj;

class PackMessage {

public:

	BufQueue*		bigMsgQueue;		// 打包的流队列
	BufPool*		bigMsgPool;			// 打包的池，貌似是因为linux的glibc不讲内存归还操作系统，所以需要这个
	int MsgSize;
	char*			curBufHead;			// 当前打包的缓冲区的头
	int 			curBufOffset;		// 当前打包的缓冲区偏移
	int				curBufEmpty;		// 当前打包的缓冲区剩余空间
public:
	PackMessage();
	~PackMessage();

	bool			PackInt(int i);
	bool			PackIntObj(int i);
	bool			PackLong(long l);
	bool			PackLongObj(long l);
	bool			PackBool(bool b);
	bool			PackBoolObj(bool b);
	bool 			PackFloat(float f);
	bool 			PackFloatObj(float f);
	bool 			PackDouble(double d);
	bool 			PackDoubleObj(double d);
	bool 			PackString(char* s, int size);
	bool 			PackStringObj(char* s, int size);
	bool 			PackBigObj(BigObj bigObj);
	int				PackSize(){return MsgSize;}
	void 			PackByte(const void* pHead, int size);
	BufQueue*		BigMsgQueue(){return bigMsgQueue;}
	void			NewBuf();			// 新建一个缓冲区

};

class UnpackMessage{
public:
	UnpackMessage(BigObj* bigObj);
	UnpackMessage(void* pHead, int nSize);
public:
	bool			UnpackInt(int i);
	bool			UnpackLong(long l);
	bool			UnpackBool(bool b);
	bool 			UnpackFloat(float f);
	bool 			UnpackDouble(double d);
};

class BigObj{
private:
	int ObjSize;
public:
	int Size(){return ObjSize;}

};

#endif //MYSLG_GENETPACK_H
