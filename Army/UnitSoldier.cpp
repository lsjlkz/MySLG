//
// Created by lsjlkz on 2021/12/23.
//

#include "UnitSoldier.h"
#include "FightHelp.h"

UnitSoldier::UnitSoldier(int id, Vector2 xy, int moveSpeed, int atk, int def, int hp) : Base<UnitSoldier>(this){
    _id = id;
    _xy = xy;
    _atk = atk;
    _def = def;
    _hp = hp;
    _moveSpeed = moveSpeed;
    _deadCallBack = new Function<UnitSoldier>(GH::SoldierDead, *this);

}

UnitSoldier::UnitSoldier(int id, Vector2 xy, int moveSpeed, int atk, int def, int hp, ArmyTroops* armyTroops) : Base<UnitSoldier>(this){
    _id = id;
    _xy = xy;
    _atk = atk;
    _def = def;
    _hp = hp;
    _moveSpeed = moveSpeed;
    _inArmyTroops = armyTroops;
    _deadCallBack = new Function<UnitSoldier>(GH::SoldierDead, *this);

}

UnitSoldier::UnitSoldier(int id, Vector2 xy, int moveSpeed, int atk, int def, int hp, int armyTroopsID) : Base<UnitSoldier>(this){
    _id = id;
    _xy = xy;
    _atk = atk;
    _def = def;
    _hp = hp;
    _moveSpeed = moveSpeed;
    _armyTroopsID = armyTroopsID;
    _deadCallBack = new Function<UnitSoldier>(GH::SoldierDead, *this);

}

long UnitSoldier::GetID() {
    return _id;
}

void UnitSoldier::Move(int x, int y) {
    _xy.IncXY(x * _moveSpeed, y * _moveSpeed);
}

bool UnitSoldier::canAttack() {
    return true;
}


int UnitSoldier::GetAtk() {
    return _atk;
}

void UnitSoldier::DecHp(UnitSoldier *army) {
    int atk = army->GetAtk();
    int decHp = std::max(atk - _def, 1);
    _hp -= decHp;
    std::cout << army->GetID() << " attack " << _id << ", dec " << decHp << " hp, left " << _hp << " hp." << std::endl;
    if(_hp <= 0){
        _deadCallBack->Call();
    }
}

void UnitSoldier::AttackSoldier(UnitSoldier *army) {
    army->DecHp(this);
}


ArmyTroops *UnitSoldier::GetArmyTroops() {
    return _inArmyTroops;
//    return ArmyManager::GetArmyTroops(_armyTroopsID);
}
