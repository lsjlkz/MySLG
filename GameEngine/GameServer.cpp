//
// Created by lsjlkz on 2022/6/2.
//

#include "GameServer.h"

int GameServer::CreateNetwork(int MaxConnect, int Thread, int Port) {
	this->geNetWork = new GENetWork(MaxConnect, Thread);
	this->geNetWork->ListenPort(Port);
	return 0;
}
