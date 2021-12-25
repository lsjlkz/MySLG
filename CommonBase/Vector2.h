//
// Created by lsjlkz on 2021/12/23.
//

#ifndef MYSLG_VECTOR2_H
#define MYSLG_VECTOR2_H


class Vector2 {
private:
    int _x=0;
    int _y=0;

public:
    Vector2(int x, int y):_x(x), _y(y){};
    Vector2(Vector2 const &xy);
    Vector2();

    void IncX(int x){
        _x += x;
    }
    void IncY(int y){
        _y += y;
    }
    void IncXY(int x, int y){
        _x += x;
        _y += y;
    }

    int GetX(){
        return _x;
    }
    int GetY(){
        return _y;
    }
};


#endif //MYSLG_VECTOR2_H
