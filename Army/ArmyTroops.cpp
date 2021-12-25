//
// Created by lsjlkz on 2021/12/24.
//

#include "ArmyTroops.h"
#include "FightHelp.h"

ArmyTroops::ArmyTroops(Vector2 centerXY, int width, int height, int moveSpeed, int atk, int def, int hp):_centerXY(centerXY), _width(width), _height(height),
                                                                                                         Base<ArmyTroops>(this){
    _id = AutoID::GetAutoID();
    std::cout << "create army " << _id << std::endl;
    _centerXY = centerXY;
    int halfWidth = width / 2 ;
    int halfHeight = height / 2;
    halfWidth = halfWidth > 0 ? halfWidth : 1;
    halfHeight = halfHeight > 0 ? halfHeight : 1;
    for(int i = centerXY.GetX() - halfWidth; i < centerXY.GetX() + halfWidth; ++i){
        for(int j = centerXY.GetX() - halfHeight; j < centerXY.GetY() + halfHeight; ++j){
            UnitSoldier* unitSoldier = GH::CreateSoldier(i,j,moveSpeed,atk,def,hp, this);
            soldierMap.insert(std::pair<int, UnitSoldier*>(unitSoldier->GetID(), unitSoldier));
        }
    };
    _targetArmyID = 0;
    _targetArmy = nullptr;
}

void ArmyTroops::AttackArmy(int armyID) {
    std::cout << _id << " attack " << armyID << std::endl;
    ArmyTroops* armyTroops = ArmyManager::Instance()->GetArmyTroops(armyID);
    if(armyTroops == nullptr){
        // 没有部队
        return;
    }
    _targetArmy = armyTroops;
    _targetArmyID = armyID;
    SetAttackBegin();
    armyTroops->DefendArmy(this);
}

void ArmyTroops::DefendArmy(ArmyTroops* army) {
    _targetArmyID = army->GetID();
    _targetArmy = army;
    SetAttackBegin();
}

void ArmyTroops::SetAttackBegin() {
    _state = StateFight;
    CircleAttackArmy();
}

void ArmyTroops::SetAttackEnd() {
    _state = StateHold;
    _targetArmyID = 0;
    _targetArmy = nullptr;

}

void ArmyTroops::SetArmyMoveTo() {
    _state = StateMove;
}

void ArmyTroops::CircleAttackArmy() {
    if(_state != StateFight){
        return;
    }
    // TODO
    std::map<int, UnitSoldier*>::iterator it;
    it = soldierMap.begin();
    while(it != soldierMap.end()){
        UnitSoldier* soldier = _targetArmy->GetOneSoldier();
        if(soldier == nullptr){
            return;
        }
        it->second->AttackSoldier(soldier);
        it++;
    }
}

void ArmyTroops::DecHp(int atk) {
    std::map<int, UnitSoldier*>::iterator it;
    it = soldierMap.begin();
    while(it != soldierMap.end()){
    }
}

UnitSoldier *ArmyTroops::GetOneSoldier() {
//    std::map<int, UnitSoldier*>::iterator it;
    auto it = soldierMap.begin();
    if(it == soldierMap.end()){
        return nullptr;
    }
    std::advance(it, rand() % soldierMap.size());
    return it->second;

}

void ArmyTroops::RemoveSoldier(int soldierID) {
    UnitSoldier* soldier = soldierMap.at(soldierID);
    if(soldier != nullptr){
        delete soldier;
        soldierMap.erase(soldierID);
    }

}


ArmyTroops* ArmyManager::CreateArmyTroops(Vector2 centerXY, int width, int height, int moveSpeed, int atk, int def, int hp) {
    ArmyTroops* armyTroops = new ArmyTroops(centerXY, width, height, moveSpeed, atk, def, hp);
    std::cout << "new army " <<armyTroops->GetID() << std::endl;
    ArmyManager::Instance()->armyMap.insert(std::pair<int, ArmyTroops*>(armyTroops->GetID(), armyTroops));
    return armyTroops;
}

ArmyTroops* ArmyManager::GetArmyTroops(int id) {
    ArmyTroops* armyTroops = ArmyManager::Instance()->armyMap.at(id);
    if(armyTroops != nullptr){
        return armyTroops;
    }
    return nullptr;
}
