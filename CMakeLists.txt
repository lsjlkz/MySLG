cmake_minimum_required(VERSION 3.20)
project(MySLG)

set(CMAKE_CXX_STANDARD 11)

add_executable(MySLG main.cpp Army/UnitSoldier.cpp Army/UnitSoldier.h CommonBase/Vector2.cpp CommonBase/Vector2.h GameEngine/Tick.cpp GameEngine/Tick.h GameEngine/Function.cpp GameEngine/Function.h GameEngine/SingleTon.h GameEngine/AutoID.cpp GameEngine/AutoID.h GameEngine/GameHelp.cpp GameEngine/GameHelp.h GameEngine/Process.cpp GameEngine/Process.h Army/ArmyTroops.cpp Army/ArmyTroops.h Army/ArmyFightDefine.h Army/FightHelp.cpp Army/FightHelp.h)
include_directories(GameEngine Army CommonBase)
link_directories(GameEngine Army CommonBase)