//
// Created by lsjlkz on 2021/12/24.
//

#include "FightHelp.h"


//回调
//TODO 外面矩阵去除这个士兵
void GH::SoldierDead(UnitSoldier unitSoldier){
    std::cout << "army:(" << unitSoldier.GetArmyTroopsID() << "):soldier(" << unitSoldier.GetID() << ") dead." <<std::endl;

    unitSoldier.GetArmyTroops()->RemoveSoldier(unitSoldier.GetID());
}


UnitSoldier* GH::CreateSoldier(int id, int x, int y, int moveSpeed, int atk, int def, int hp, ArmyTroops* armyTroops){

    UnitSoldier* unitSoldier = new UnitSoldier(id, Vector2(x, y), moveSpeed, atk, def, hp, armyTroops);
    return unitSoldier;
}
UnitSoldier* GH::CreateSoldier(int id, int x, int y, int moveSpeed, int atk, int def, int hp, int armyTroopsID){

    UnitSoldier* unitSoldier = new UnitSoldier(id, Vector2(x, y), moveSpeed, atk, def, hp, armyTroopsID);
    return unitSoldier;
}

UnitSoldier* GH::CreateSoldier(int id, int x, int y, int moveSpeed, int atk, int def, int hp){

    UnitSoldier* unitSoldier = new UnitSoldier(id, Vector2(x, y), moveSpeed, atk, def, hp);
    return unitSoldier;
}

void GH::ArmyTroopsDead(ArmyTroops armyTroopsDead) {
    std::cout << armyTroopsDead.GetID() << " dismiss." <<std::endl;

    ArmyManager::Instance()->AddDeadArmy(armyTroopsDead.GetID());

}


