//
// Created by lsjlkz on 2022/6/2.
//

#include "LuaGameServer.h"

int LuaGameServer::CreateNetwork(int MaxConnect, int Thread, int Port) {
	return GameServer::Instance()->CreateNetwork(MaxConnect, Thread, Port);
}

int create_network(lua_State* L){
	luaL_checktype(L, 1, LUA_TNUMBER);
	luaL_checktype(L, 2, LUA_TNUMBER);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int maxCount = (int) lua_tointeger(L, 1);
	int thread = (int) lua_tointeger(L, 2);
	int port = (int) lua_tointeger(L, 3);
	lua_settop(L, 0);
	int ret = LuaGameServer::CreateNetwork(maxCount, thread, port);
	lua_pushnumber(L, ret);
	return 1;
}

int luaopen_luagameserver_libs(lua_State *L) {
	luaL_newmetatable(L, "LuaGameServer");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, lua_reg_gameserver_func, 0);
	// 创建新表，压函数
//	luaL_newlib(L, lua_reg_gameserver_create_funcs);
	return 1;
}
