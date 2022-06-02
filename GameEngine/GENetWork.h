//
// Created by lsjlkz on 2022/6/2.
//

#ifndef MYSLG_GENETWORK_H
#define MYSLG_GENETWORK_H

#include "iostream"

// 网络层
class GENetWork{
public:
	GENetWork(int MaxConnect, int Thread);
	int ListenPort(int Port);
};


#endif //MYSLG_GENETWORK_H
