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
            UnitSoldier* unitSoldier = GH::CreateSoldier(i * width + j, i,j,moveSpeed,atk,def,hp, this);
            soldierMap.insert(std::pair<int, UnitSoldier*>(unitSoldier->GetID(), unitSoldier));
        }
    };
    _targetArmyID = 0;
    _targetArmy = nullptr;
    // 创建回调
    _deadCallBack = new Function<ArmyTroops>(GH::ArmyTroopsDead, *this);
}

void ArmyTroops::AttackArmy(int armyID) {
    // 攻击一个部队
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
    // 防守，也是攻击
    _targetArmyID = army->GetID();
    _targetArmy = army;
    SetAttackBegin();
}

void ArmyTroops::SetAttackBegin() {
    // 打架中
    _state = StateFight;
    ArmyManager::Instance()->AddAttackArmy(_id);
}

void ArmyTroops::SetAttackEnd() {
    // 结束了
    _state = StateHold;
    _targetArmyID = 0;
    _targetArmy = nullptr;
    // 从攻击的移除
    ArmyManager::Instance()->RemoveAttackArmy(_id);

}

void ArmyTroops::SetArmyMoveTo() {
    _state = StateMove;
}

bool ArmyTroops::CircleAttackArmy() {
    // 部队攻击循环
    // 若部队不攻击了，return
    if(_state != StateFight){
        return false;
    }
    // 如果没有士兵了
    if(soldierMap.empty()){
        // 停止攻击
        _targetArmy->SetAttackEnd();
        // 敌方停止攻击
        SetAttackEnd();
        // 死亡回调
        _deadCallBack->Call();
        return false;
    }
    // 还有士兵
    std::map<int, UnitSoldier*>::iterator it;
    it = soldierMap.begin();
    // 让每一个士兵都攻击一下
    while(it != soldierMap.end()){
        if(!it->second->canAttack()){
            continue;
        }
        // 获取对面的一个士兵来攻击
        UnitSoldier* soldier = _targetArmy->GetOneSoldier();
        if(soldier == nullptr){
            continue;
        }
        // 攻击随机的这个士兵
        it->second->AttackSoldier(soldier);
        it++;
    }
    return true;
}

void ArmyTroops::DecHp(int atk) {
    // 部队扣血
    std::map<int, UnitSoldier*>::iterator it;
    it = soldierMap.begin();
    while(it != soldierMap.end()){
        it++;
    }
}

UnitSoldier *ArmyTroops::GetOneSoldier() {
    // 获取一个士兵
    auto it = soldierMap.begin();
    if(it == soldierMap.end()){
        return nullptr;
    }
    std::advance(it, rand() % soldierMap.size());
    return it->second;

}

void ArmyTroops::RemoveSoldier(int soldierID) {
    // 移除一个士兵
    UnitSoldier* soldier = soldierMap.at(soldierID);
    if(soldier != nullptr){
        delete soldier;
        soldierMap.erase(soldierID);
    }
}


ArmyTroops* ArmyManager::CreateArmyTroops(Vector2 centerXY, int width, int height, int moveSpeed, int atk, int def, int hp) {
    // 生成一个部队
    ArmyTroops* armyTroops = new ArmyTroops(centerXY, width, height, moveSpeed, atk, def, hp);
    std::cout << "new army " <<armyTroops->GetID() << std::endl;
    // 添加近部队字典中
    armyMap.insert(std::pair<int, ArmyTroops*>(armyTroops->GetID(), armyTroops));
    return armyTroops;
}

ArmyTroops* ArmyManager::GetArmyTroops(int id) {
    // 通过id获取部队
    ArmyTroops* armyTroops = armyMap.at(id);
    if(armyTroops != nullptr){
        return armyTroops;
    }
    return nullptr;
}

void ArmyManager::RemoveArmyTroops(int id) {
    // 部队死亡，从部队列表中移除
    std::remove(attackArmyVec.begin(), attackArmyVec.end(), id);
    ArmyTroops* armyTroops = armyMap.at(id);
    if(armyTroops != nullptr){
        armyMap.erase(id);
        delete armyTroops;
    }
}


bool ArmyManager::CircleAttack() {
    // 循环攻击的函数
    auto it = armyMap.begin();
    bool fightFlag = false;
    while(it != armyMap.end()){
        fightFlag = it->second->CircleAttackArmy()? true:fightFlag;
        it++;
    }
    return fightFlag;
}

void ArmyManager::AddDeadArmy(int id) {
    // 记录一下死亡的部队，方便回调中处理掉
    deadArmyVec.emplace_back(id);
}

bool ArmyManager::CircleCheckDead() {
    // 循环检查死亡的部队列表，然后移除
    auto it = deadArmyVec.begin();
    while(it != deadArmyVec.end()){
        RemoveArmyTroops(*it);
        it++;
    }
    deadArmyVec.clear();
    return true;
}

bool ArmyManager::CircleFunc() {
    // 部队管理循环
    bool flag = false;
    if(!attackArmyVec.empty()){
        flag = CircleAttack() ? true : flag;
    }
    if(!deadArmyVec.empty()){
        flag = CircleCheckDead() ? true : flag;
    }
    return flag;
}

void ArmyManager::AddAttackArmy(int id) {
    // 添加攻击的部队
    attackArmyVec.emplace_back(id);
}

void ArmyManager::RemoveAttackArmy(int id) {
    // 部队不攻击了，移除
    std::remove(attackArmyVec.begin(), attackArmyVec.end(), id);
}


