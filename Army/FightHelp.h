//
// Created by lsjlkz on 2021/12/24.
//

#ifndef MYSLG_FIGHTHELP_H
#define MYSLG_FIGHTHELP_H



#include <UnitSoldier.h>
//#include "ArmyTroops.h"

namespace GH{
    // 死亡回调
    void SoldierDead(UnitSoldier unitSoldier);
    UnitSoldier* CreateSoldier(int id, int x, int y, int moveSpeed, int atk, int def, int hp, ArmyTroops* armyTroops);
    UnitSoldier* CreateSoldier(int id, int x, int y, int moveSpeed, int atk, int def, int hp, int armyTroopsID);
    UnitSoldier* CreateSoldier(int id, int x, int y, int moveSpeed, int atk, int def, int hp);

    void ArmyTroopsDead(ArmyTroops armyTroopsDead);
}



#endif //MYSLG_FIGHTHELP_H
