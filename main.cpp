#include "LuaHelp.h"
#include "thread"

void circle_func(){
    while(ArmyManager::Instance()->CircleFunc());
    std::cout << "fight end." << std::endl;
}

void TestArmy() {
	Vector2 vector2(3, 3);
	ArmyTroops *armyTroops1 = ArmyManager::Instance()->CreateArmyTroops(vector2, 1, 1, 1, 1, 1, 1);
	ArmyTroops *armyTroops2 = ArmyManager::Instance()->CreateArmyTroops(vector2, 2, 2, 2, 2, 2, 2);
	armyTroops1->AttackArmy(armyTroops2->GetID());
}

int main(int argc, char* argv[]) {
	AutoID::New();
	ArmyManager::New();
	GameServer::New();
	GameServer::Instance()->Init(argv);
	LuaEngine::New();
	LuaEngine::Instance()->Init();
	RegLuaModule();
	LuaEngine::Instance()->DoFile("../LuaCode/Server/GSInit.lua");
    return 0;
}
