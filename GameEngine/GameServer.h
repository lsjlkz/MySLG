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
	void SetGameServerID(int id);
	int GetGameServerID(){return GameServerID;};
	int Init(char* argv[]);

private:
	GENetWork* geNetWork;
	int GameServerID = 0;
};


#endif //MYSLG_GAMESERVER_H
