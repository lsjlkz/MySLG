//
// Created by lsjlkz on 2021/12/24.
//

#include "FightHelp.h"


//回调
//TODO 外面矩阵去除这个士兵
void GH::SoldierDead(UnitSoldier unitSoldier){
    std::cout << unitSoldier.GetID() << "士兵死了" <<std::endl;

//    unitSoldier.GetArmyTroops()->RemoveSoldier(unitSoldier.GetID());
}


//UnitSoldier GH::CreateSoldier(int x, int y, int moveSpeed, int atk, int def, int hp, ArmyTroops* armyTroops){
UnitSoldier* GH::CreateSoldier(int x, int y, int moveSpeed, int atk, int def, int hp){

//    UnitSoldier unitSoldier(Vector2(x, y), moveSpeed, atk, def, hp, ArmyTroops* armyTroops);
    UnitSoldier* unitSoldier = new UnitSoldier(Vector2(x, y), moveSpeed, atk, def, hp);
    return unitSoldier;
}


