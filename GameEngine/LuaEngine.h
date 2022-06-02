//
// Created by lsjlkz on 2022/5/23.
//

#pragma once
#ifndef MYSLG_LUAENGINE_H
#define MYSLG_LUAENGINE_H

#include "SingleTon.h"

extern "C"{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}
// 需要加上这一行才行
#pragma comment(lib, "Lua.lib")

class LuaEngine:public SingleTon<LuaEngine>{
private:
	// lua_State是主线程、栈、和数据结构
	// 用于函数调用与和c通信
	lua_State *L;
	// 全局状态机，管理全局数据
	// static global_State *G;
	std::vector<luaL_Reg> RegList;
public:
	lua_State* GetLuaState(){
		return L;
	}
	bool Init();
	bool Del();

	void RegAppend(luaL_Reg lReg);
	int LuaReg();

	int LoadFile(const char* filepath);
	int DoFile(const char* filepath);

	void test();


	// 执行一段lua code
	int executeString(const char* codes);

};


#endif //MYSLG_LUAENGINE_H
