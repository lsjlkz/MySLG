//
// Created by lsjlkz on 2022/6/16.
//

#ifndef MYSLG_GEDEFINE_H
#define MYSLG_GEDEFINE_H

#ifdef WIN
#define WIN_ASSERT
#endif

#ifdef WIN_ASSERT
#define GE_WIN_ASSERT(exp) if (!(exp)){ std::abort(); }
#else
#define GE_WIN_ASSERT(exp)
#endif


class GEDefine {

};


#endif //MYSLG_GEDEFINE_H
