//
// Created by lsjlkz on 2021/12/23.
//

#include "Tick.h"

long Tick::RegTick(int timeSec, Function<void *> callBack) {
    _id = AutoID::GetAutoID();
    return _id;
}

