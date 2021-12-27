//#include <iostream>
#include "GameHelp.h"
#include "ArmyTroops.h"




int main() {
    AutoID::New();
    ArmyManager::New();
    Vector2 vector2(3,3);
    ArmyTroops* armyTroops1 = ArmyManager::Instance()->CreateArmyTroops(vector2, 1,1,1,1,1,1);
    ArmyTroops* armyTroops2 = ArmyManager::Instance()->CreateArmyTroops(vector2, 2,2,2,2,2,2);
    armyTroops1->AttackArmy(armyTroops2->GetID());
    while(ArmyManager::Instance()->CircleFunc());
    std::cout << "fight end." << std::endl;
    return 0;
}
