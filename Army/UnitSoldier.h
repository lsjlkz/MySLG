//
// Created by lsjlkz on 2021/12/23.
//

#pragma once
#ifndef MYSLG_UNITSOLDIER_H
#define MYSLG_UNITSOLDIER_H


#include <utility>
#include <iostream>
#include <Vector2.h>

#include "AutoID.h"
#include "Function.h"
#include "ArmyTroops.h"

class ArmyTroops;


class UnitSoldier:public Base<UnitSoldier>{
private:
    int _id;
    Vector2 _xy;
    int _moveSpeed;
    int _atk;
    int _def;
    int _hp;
    int _armyTroopsID;
    ArmyTroops* _inArmyTroops;

public:
    Function<UnitSoldier>* _deadCallBack;


public:
    UnitSoldier(int id, Vector2 xy, int moveSpeed, int atk, int def, int hp, ArmyTroops* armyTroops);
    UnitSoldier(int id, Vector2 xy, int moveSpeed, int atk, int def, int hp, int armyTroopsID);
    UnitSoldier(int id, Vector2 xy, int moveSpeed, int atk, int def, int hp);

    long GetID();

    void Move(int x, int y);

    Vector2 GetXY(){
        return _xy;
    }

    virtual bool canAttack();

    void DecHp(UnitSoldier* unitSoldier);

    void AttackSoldier(UnitSoldier* army);

    int GetAtk();

    ArmyTroops* GetArmyTroops();

    int GetArmyTroopsID(){return _armyTroopsID;}

};



#endif //MYSLG_UNITSOLDIER_H
