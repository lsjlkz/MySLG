//
// Created by lsjlkz on 2022/6/2.
//

#ifndef MYSLG_LUAGAMESERVER_H
#define MYSLG_LUAGAMESERVER_H

#include "GameServer.h"
#include "LuaEngine.h"

int create_network(lua_State* L);

static const luaL_Reg lua_reg_gameserver_func[] = {
		{"CreateNetwork", create_network},
		{NULL, NULL}
};

static const luaL_Reg lua_reg_gameserver_create_funcs[] = {
		{NULL, NULL}
};

int luaopen_luagameserver_libs(lua_State* L);

class LuaGameServer{
public:
	static int CreateNetwork(int MaxConnect, int Thread, int Port);
};


#endif //MYSLG_LUAGAMESERVER_H
