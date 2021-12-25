//
// Created by lsjlkz on 2021/12/23.
//

#include "UnitSoldier.h"
#include "FightHelp.h"

//UnitSoldier::UnitSoldier(Vector2 xy, int moveSpeed, int atk, int def, int hp, ArmyTroops* armyTroops) : Base<UnitSoldier>(this){
UnitSoldier::UnitSoldier(Vector2 xy, int moveSpeed, int atk, int def, int hp) : Base<UnitSoldier>(this){
    _id = AutoID::GetAutoID();
    _xy = xy;
    _atk = atk;
    _def = def;
    _hp = hp;
    _moveSpeed = moveSpeed;
//    _inArmyTroops = armyTroops;
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
    std::cout << army->GetID() << "attack " << _id << "，dec " << decHp << " hp，left " << _hp << " hp.";
    if(_hp <= 0){
        _deadCallBack->Call();
    }
}

void UnitSoldier::AttackSoldier(UnitSoldier *army) {
    army->DecHp(this);
}

//ArmyTroops *UnitSoldier::GetArmyTroops() {
//    return _inArmyTroops;
//}
