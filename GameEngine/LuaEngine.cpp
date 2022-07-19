//
// Created by lsjlkz on 2022/5/23.
//


#include "LuaEngine.h"

void LuaEngine::test() {
	lua_State *L = luaL_newstate();
	if(L == nullptr){
		std::cout << "Create lua State Error" << std::endl;
		return;
	}
	luaL_openlibs(L);
	int ret = luaL_dofile(L, "../LuaCode/test.lua");
	if(ret){
		std::cout << "lua dofile err" << std::endl;
		return;
	}
	lua_getglobal(L, "str");
	std::cout << "str is " << lua_tostring(L, -1) << std::endl;
	lua_getglobal(L, "tb");
	lua_getfield(L, -1, "name");
	std::cout << "name in tb is " << lua_tostring(L, -1) << std::endl;
	lua_getglobal(L, "print_test");
	lua_pcall(L, 0, 0, 0);

	lua_getglobal(L, "add");
	lua_pushnumber(L, 1);
	lua_pushnumber(L, 2);
	lua_pcall(L, 2, 1, 0);
	if(lua_isnumber(L, -1)){
		std::cout << "result is " << lua_tonumber(L, -1) << std::endl;
	}
	lua_close(L);
}

bool LuaEngine::Del() {
	if(L == nullptr){
		std::cout << "close lua_state repeat" << std::endl;
		return false;
	}
	lua_close(L);
	L = nullptr;
	return true;
}

bool LuaEngine::Init() {
	if(L != nullptr){
		std::cout << "new lua_state repeat" << std::endl;
		return false;
	}
	L = luaL_newstate();
	luaL_openlibs(L);
	executeString("LuaEngine Init Successfully");
	return true;
}

int LuaEngine::executeString(const char *codes) {
	if(L == nullptr){
		std::cout << "lua engine not init" << std::endl;
		return 0;
	}
	luaL_dostring(L, codes);
	return 0;
}

int LuaEngine::LuaReg() {
	return 0;
}

void LuaEngine::RegAppend(luaL_Reg lReg) {
	RegList.push_back(lReg);
}

int LuaEngine::LoadFile(const char *filepath) {
	int ret = luaL_loadfile(L, filepath);
	if(ret){
		std::cout << "load lua file error:(" << filepath << ")" << std::endl;
	}
	return ret;
}

int LuaEngine::DoFile(const char *filepath) {
	if(luaL_dofile(L, filepath)){
		std::cout << lua_tostring(L, -1) << std::endl;;
	}
	return 0;
}

