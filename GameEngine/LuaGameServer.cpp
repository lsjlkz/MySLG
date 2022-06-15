//
// Created by lsjlkz on 2022/6/2.
//

#include "LuaGameServer.h"

int LuaGameServer::CreateNetwork(int MaxConnect, int Thread, int Port) {
	return GameServer::Instance()->CreateNetwork(MaxConnect, Thread, Port);
}

int LuaGameServer::GetGameServerID() {
	return GameServer::Instance()->GetGameServerID();
}

int LuaGameServer::RegLuaFunc(lua_State *L) {
	// 获取这个函数
	// TODO
	// 对函数名字存到hashmap里，还有这个key和ref，需要调用的时候就直接通过全局表获取到这个ref，然后call
//	int key = luaL_ref(L, 0);
//	// 清空栈
//	lua_settop(L, 0);
//	luaL_getmetatable(L, "LuaFunction");
//	// 创建一个全局注册表，然后把所有的lua注册函数放到这里
//	luaL_newmetatable(L, "LuaFunction");
//	//将元表作为一个副本压栈到位置-1，刚刚创建的元表位置-2
//	lua_pushvalue(L, -1);
//	lua_setfield(L, -2, "__index");
	return 0;
}

int LuaGameServer::CallLuaFunc(int funcID, const char* p) {
	lua_State *L = LuaEngine::Instance()->GetLuaState();
	if(L == nullptr){
		std::cout << "Create lua State Error" << std::endl;
		return 1;
	}
	int ret = luaL_loadfile(L, "../LuaCode/Common/Game/Function.lua");
	if(ret){
		std::cout << "lua dofile err" << std::endl;
		return 1;
	}
	// 获取元表
	lua_getglobal(L, "__G__FunctionTable");
	// 获取函数分发函数
	lua_pushstring(L, "TriMesFunction");
	lua_gettable(L, -2);
	lua_pushinteger(L, funcID);
	lua_pushstring(L, p);
	ret = lua_pcall(L, 2, 0, 0);
	if(ret){
		std::cout << "lua call err" << std::endl;
	}
	return 0;
}

int LuaGameServer::CallLuaFunc(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int funcID = lua_tointeger(L, 1);
	const char* p = lua_tostring(L, 2);
	return CallLuaFunc(funcID, p);
}

int reg_lua_func(lua_State* L){
	return 0;
}

int call_lua_func(lua_State *L){
	return LuaGameServer::CallLuaFunc(L);
}

int get_gameserver_id(lua_State* L){
	lua_settop(L, 0);
	lua_pushinteger(L, LuaGameServer::GetGameServerID());
	return 1;
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
