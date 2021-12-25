//#include <iostream>
#include "GameHelp.h"
#include "ArmyTroops.h"
//
//class B:public Base<int>{
//public:
//    B(int* a):Base<int>(a){
//    }
//    int get(){
//        return 3;
//    }
//};
//
//void p(B a){
//    std::cout << a.get() << std::endl;
//}






int main() {
//    Function<B>* b = new Function<B>(p, B(new int(3)));
//    b->Call();
    AutoID::New();
    ArmyManager::New();
    Vector2 vector2(3,3);
    ArmyTroops* armyTroops1 = ArmyManager::Instance()->CreateArmyTroops(vector2, 1,1,1,1,1,1);
    ArmyTroops* armyTroops2 = ArmyManager::Instance()->CreateArmyTroops(vector2, 2,2,2,2,2,2);
    armyTroops1->AttackArmy(armyTroops2->GetID());

    return 0;
}
