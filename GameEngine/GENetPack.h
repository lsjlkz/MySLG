//
// Created by lsjlkz on 2022/6/15.
//

#ifndef MYSLG_GENETPACK_H
#define MYSLG_GENETPACK_H

#include <vector>
#include <list>
#include "LuaEngine.h"
#include "GEDefine.h"

#define IntFlag					-1
#define LongFlag				-2
#define BoolFlag				-3
#define FloatFlag				-4
#define DoubleFlag				-5
#define StringFlag				-6
#define CharFlag				-7

#define NoneFlag				-100
#define TrueFlag				-101
#define FalseFlag				-102
#define TableFlag				-103
#define BinFlag					-104
#define DateTimeFlag			-105

#define MSG_MAX_SIZE			65536		// 最大char长度
#define MAX_STACK_DEEP			30			// 最大递归层数

#define ASSERT_LUA_TOP(L, top, i)	\
	if (top + i != lua_gettop(L)) { std::abort(); };

typedef std::vector<char*>			BufPool;
typedef std::list<char*>			BufQueue;

// 这个模块即将会很庞大，貌似


class PackMessage {

public:

	BufQueue*		bigMsgQueue;		// 打包的流队列
	BufPool*		bigMsgPool;			// 打包的池，貌似是因为linux的glibc不讲内存归还操作系统，所以需要这个
	int MsgSize;
	char*			curBufHead;			// 当前打包的缓冲区的头
	int 			curBufOffset;		// 当前打包的缓冲区偏移
	int				curBufEmpty;		// 当前打包的缓冲区剩余空间
	int				curStackDeep;		// 栈深度，防止递归自身
public:
	PackMessage();
	~PackMessage();

	bool			PackType(int t);
	bool 			PackCharInt(int c);
	bool 			PackChar(char c);
	bool			PackInt(int i);
	int&			PackIntRef();
	bool			PackIntObj(int i);
	bool			PackLong(long l);
	bool			PackLongObj(long l);
	bool			PackBool(bool b);
	bool			PackBoolObj(bool b);
	bool 			PackFloat(float f);
	bool 			PackFloatObj(float f);
	bool 			PackDouble(double d);
	bool 			PackDoubleObj(double d);
	bool 			PackString(const char* s, int size);
	bool 			PackStringObj(const char *s, int size);
	bool 			PackLuaObj(lua_State* L);
	bool 			PackLuaHelp(lua_State* L, int index);
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

#endif //MYSLG_GENETPACK_H
