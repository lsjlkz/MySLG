//
// Created by lsjlkz on 2021/12/24.
//

#include "ArmyTroops.h"
#include "FightHelp.h"

ArmyTroops::ArmyTroops(Vector2 centerXY, int width, int height, int moveSpeed, int atk, int def, int hp):_centerXY(centerXY), _width(width), _height(height),
                                                                                                         Base<ArmyTroops>(this){
    _id = AutoID::GetAutoID();
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
			it++;
            continue;
        }
        // 获取对面的一个士兵来攻击
        UnitSoldier* soldier = _targetArmy->GetOneSoldier();
        if(soldier == nullptr){
			it++;
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
    // 添加近部队字典中
	std::cout << "army:" << moveSpeed << "," << atk << "," << def << "," << hp << std::endl;
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
        flag = CircleAttack() || flag;
    }
    if(!deadArmyVec.empty()){
        flag = CircleCheckDead() || flag;
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

int lua_create_new_army(lua_State* L){
	// 参数：x, y, width, height, speed, atk, def, hp
	luaL_checktype(L, 1, LUA_TNUMBER);
	luaL_checktype(L, 2, LUA_TNUMBER);
	luaL_checktype(L, 3, LUA_TNUMBER);
	luaL_checktype(L, 4, LUA_TNUMBER);
	luaL_checktype(L, 5, LUA_TNUMBER);
	luaL_checktype(L, 6, LUA_TNUMBER);
	luaL_checktype(L, 7, LUA_TNUMBER);
	luaL_checktype(L, 8, LUA_TNUMBER);
	Vector2 vector2((int)lua_tointeger(L, 1),(int)lua_tointeger(L, 2));
	int width = (int)lua_tointeger(L, 3);
	int height = (int)lua_tointeger(L, 4);
	int moveSpeed = (int)lua_tointeger(L, 5);
	int atk = (int)lua_tointeger(L, 6);
	int def = (int)lua_tointeger(L, 7);
	int hp = (int)lua_tointeger(L, 8);
	// 清空栈
	lua_settop(L, 0);
	// 先构造Lua对象可识别的指针
	ArmyTroops** pArmyTroopsRef = (ArmyTroops**) lua_newuserdata(L, sizeof(ArmyTroops*));
	// 用这个指针指向的地方构造一个类实例
	*pArmyTroopsRef = ArmyManager::Instance()->CreateArmyTroops(
			vector2, width,height,moveSpeed,atk,def,hp);
	luaL_getmetatable(L, "ArmyTroops");
	lua_setmetatable(L, -2);
	return 1;
}

int lua_army_attack(lua_State* L){
	// 参数：army,otherArmy
	ArmyTroops** army = (ArmyTroops**)luaL_checkudata(L, 1, "ArmyTroops");
	ArmyTroops** otherArmy = (ArmyTroops**)luaL_checkudata(L, 2, "ArmyTroops");
	// 清空栈
	lua_settop(L, 0);
	(*army)->AttackArmy((*otherArmy)->GetID());
	return 0;
}

int lua_army_get_id(lua_State* L){
	// 参数army
	ArmyTroops** army = (ArmyTroops**)luaL_checkudata(L, 1, "ArmyTroops");
	// 清空栈
	lua_settop(L, 0);
	lua_pushinteger(L, (*army)->GetID());
	return 1;
}

int lua_army_auto_gc(lua_State* L){
	ArmyTroops** army = (ArmyTroops**)luaL_checkudata(L, 1, "ArmyTroops");
	luaL_argcheck(L, army != nullptr, 1, "invalid user data");
	if(army){
		delete *army;
	}
	return 0;
}

int luaopen_army_libs(lua_State *L){
	//创建全局元表，如果LUA_REGISTRYINDEX注册表没有这个元表，创建一个新表添加到注册表中
	luaL_newmetatable(L, "ArmyTroops");
	//将元表作为一个副本压栈到位置-1，刚刚创建的元表位置-2
	lua_pushvalue(L, -1);

	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, lua_reg_army_funcs, 0);
	// 创建新表，压函数
	luaL_newlib(L, lua_reg_army_create_funcs);
	return 1;
}


