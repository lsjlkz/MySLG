//
// Created by lsjlkz on 2021/12/23.
//

#pragma once
#ifndef MYSLG_FUNCTION_H
#define MYSLG_FUNCTION_H
#include <functional>


// 参数基类
template<class T>
class Base{
protected:
    T* m_Param;
public:
    Base(T* param){
        m_Param = param;
    }
};

// 回调函数
template<typename Base>
class Function{
private:
    std::function<void(Base)> m_CallBack;
    Base m_Args;
public:
    Function(std::function<void(Base)> callback, Base args):m_CallBack(callback), m_Args(args){}
    // 调用回调函数
    void Call(){
        m_CallBack(m_Args);
    }

};

#endif //MYSLG_FUNCTION_H
