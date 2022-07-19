//
// Created by lsjlkz on 2022/6/2.
//

#ifndef MYSLG_LUAGAMESERVER_H
#define MYSLG_LUAGAMESERVER_H

#include "GameServer.h"
#include "LuaEngine.h"
#include "GENetPack.h"


class LuaGameServer{
private:
	std::unordered_map<int, int> map;
public:
	static int GetGameServerID();
	static int CreateNetwork(int MaxConnect, int Thread, int Port);
	static int RegLuaFunc(lua_State* L);		// 这个可能不需要，因为C无法保存lua的函数，所以函数分发可能是放在lua中
	static int CallLuaFunc(int funcID, const char* p);		// 这个是C调用lua的，而不是lua调用C调用lua的，所以这里不需要参数
	static int CallLuaFunc(lua_State* L);		// 这个是C调用lua的，而不是lua调用C调用lua的，所以这里不需要参数
	static int PackMsg(lua_State* L);
	static int DebugRecvMsg(char* s, int size);
};



int create_network(lua_State* L);
int get_gameserver_id(lua_State* L);
int reg_lua_func(lua_State* L);
int call_lua_func(lua_State* L);
int pack_msg(lua_State* L);

static const luaL_Reg lua_reg_gameserver_func[] = {
		{"CreateNetwork", create_network},
		{"GetGameServerID", get_gameserver_id},
		{"CallLuaFunc", call_lua_func},
		{"PackMsg", pack_msg},
		{NULL, NULL}
};

static const luaL_Reg lua_reg_gameserver_create_funcs[] = {
		{NULL, NULL}
};

int luaopen_luagameserver_libs(lua_State* L);



#endif //MYSLG_LUAGAMESERVER_H
