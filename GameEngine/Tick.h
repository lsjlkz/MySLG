//
// Created by lsjlkz on 2021/12/23.
//

#pragma once
#ifndef MYSLG_TICK_H
#define MYSLG_TICK_H

#include "map"
#include "AutoID.h"
#include "Function.h"


class Tick:public SingleTon<Tick> {
private:
    long _id;
    typedef std::map<long, Function<void*>>   tickReactor;
public:
    Tick(void);
    ~Tick(void);




    long RegTick(int timeSec, Function<void*> callBack);


};


#endif //MYSLG_TICK_H
