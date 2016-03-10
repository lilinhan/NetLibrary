/*************************************************************************
    > File Name: Time.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月05日 星期六 13时28分24秒
 ************************************************************************/
#ifndef _TIMER_CPP_
#define _TIMER_CPP_

#include"Timer.h"

namespace NetworkLib {
    void Timer::set_task(void (*p)(int), unsigned int t) {
        time = t;
        signal(SIGALRM, p);
        alarm(time);
    }
}

#endif
