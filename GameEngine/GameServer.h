//
// Created by lsjlkz on 2022/6/2.
//

#ifndef MYSLG_GAMESERVER_H
#define MYSLG_GAMESERVER_H

#include "SingleTon.h"
#include "GENetWork.h"
class GameServer: public SingleTon<GameServer>{
public:
	int CreateNetwork(int MaxConnect, int Thread, int Port);

private:
	GENetWork* geNetWork;
};


#endif //MYSLG_GAMESERVER_H
