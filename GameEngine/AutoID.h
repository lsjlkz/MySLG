//
// Created by lsjlkz on 2021/12/23.
//

#pragma once
#ifndef MYSLG_AUTOID_H
#define MYSLG_AUTOID_H

#include <ctime>
#include "SingleTon.h"
#include "time.h"

class AutoID:public SingleTon<AutoID> {
private:
    static long curID;
public:
    AutoID(){};
    ~AutoID(){};
    static long GetAutoID(){
        return ++curID;
    }

    static long GetCurID(){
        return curID;
    }

};


#endif //MYSLG_AUTOID_H
