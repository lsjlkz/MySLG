//
// Created by lsjlkz on 2021/12/23.
//

#include "Vector2.h"

Vector2::Vector2(Vector2 const &xy) {
    _x = xy._x;
    _y = xy._y;
}

Vector2::Vector2() {
    _x = 0;
    _y = 0;
}
