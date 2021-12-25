//
// Created by lsjlkz on 2021/12/24.
//
#pragma once
#ifndef MYSLG_ARMYTROOPS_H
#define MYSLG_ARMYTROOPS_H

#include <Vector2.h>
#include <map>
#include <vector>
#include "AutoID.h"
#include "Function.h"
#include "UnitSoldier.h"
#include "ArmyFightDefine.h"

class UnitSoldier;

class ArmyTroops:public Base<ArmyTroops> {
private:
    Vector2 _centerXY;
    int _width;
    int _height;
    long _id;
    int _targetArmyID;
    int _state;
    ArmyTroops* _targetArmy;

    std::map<int, UnitSoldier*> soldierMap;

public:
    ArmyTroops(Vector2 centerXY, int width, int height, int moveSpeed, int atk, int def, int hp);
    void AttackArmy(int armyID);    // 攻击这个部队，搞他
    void DefendArmy(ArmyTroops* army);    // 防守这个部队，搞他
    void StopAttack();
    UnitSoldier* GetOneSoldier();
    long GetID(){return _id;}
    void SetAttackBegin();
    void SetAttackEnd();
    void CircleAttackArmy();
    void SetArmyMoveTo();
    void DecHp(int atk);
    void RemoveSoldier(int soldierID);
};

class ArmyManager:public SingleTon<ArmyManager>{
private:
    std::map<int, ArmyTroops*> armyMap;


public:
    void Init(int armyMaxCount){};
    ArmyTroops* CreateArmyTroops(Vector2 centerXY, int width, int height, int moveSpeed, int atk, int def, int hp);
    static ArmyTroops* GetArmyTroops(int id);
};

#endif //MYSLG_ARMYTROOPS_H
