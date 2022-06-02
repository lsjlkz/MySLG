//
// Created by lsjlkz on 2022/5/24.
//

#ifndef MYSLG_LUAHELP_H
#define MYSLG_LUAHELP_H

#include "ArmyTroops.h"
#include "LuaGameServer.h"

static luaL_Reg lua_reg_libs[] = {
		{"base", luaopen_base},
		{"army_ctrl", luaopen_army_libs},
		{"cGameServer", luaopen_luagameserver_libs},
		{NULL, NULL}
};

static void RegLuaModule(){
	lua_State* L = LuaEngine::Instance()->GetLuaState();
	const luaL_Reg* lua_reg = lua_reg_libs;
	// 注册lua库
	for(;lua_reg->func; ++lua_reg){
		luaL_requiref(L, lua_reg->name, lua_reg->func, 1);
		lua_pop(L, 1);
	}
}

#endif //MYSLG_LUAHELP_H
