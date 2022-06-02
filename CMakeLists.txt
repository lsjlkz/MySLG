cmake_minimum_required(VERSION 3.20)
project(MySLG)

set(CMAKE_CXX_STANDARD 11)


set(INC_DIR ${PROJECT_SOURCE_DIR}/Third/Include)
set(LINK_DIR ${PROJECT_SOURCE_DIR}/Third/CLib)
include_directories(${INC_DIR})
link_directories(${LINK_DIR})

include_directories(GameEngine Army CommonBase)
link_directories(GameEngine Army CommonBase)

add_executable(MySLG main.cpp Army/UnitSoldier.cpp Army/UnitSoldier.h CommonBase/Vector2.cpp CommonBase/Vector2.h GameEngine/Tick.cpp GameEngine/Tick.h GameEngine/Function.cpp GameEngine/Function.h GameEngine/SingleTon.h GameEngine/AutoID.cpp GameEngine/AutoID.h GameEngine/GameHelp.cpp GameEngine/GameHelp.h GameEngine/Process.cpp GameEngine/Process.h Army/ArmyTroops.cpp Army/ArmyTroops.h Army/ArmyFightDefine.h Army/FightHelp.cpp Army/FightHelp.h GameEngine/LuaEngine.cpp GameEngine/LuaEngine.h GameEngine/LuaHelp.h GameEngine/LuaGameServer.cpp GameEngine/LuaGameServer.h GameEngine/GameServer.cpp GameEngine/GameServer.h GameEngine/GENetWork.cpp GameEngine/GENetWork.h)
