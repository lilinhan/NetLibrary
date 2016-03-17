/*************************************************************************
    > File Name: Timer.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月17日 星期四 14时46分53秒
 ************************************************************************/
#ifndef _TIMER_CPP_
#define _TIMER_CPP_

#include"Timer.h"
#include"Timestamp.h"

using namespace NetworkLib;

Timer::Timer(const TimerCallBack &cb, Timestamp when, double interval):
    CallBack_(cb),expiration_(when),interval_(interval),repeat_(interval > 0.0) {}

void run() const {
    CallBack_();
}

Timestamp Timer::getExpiration() const {
    return expiration_;
}

bool Timer::ifRepeat() const {
    return repeat_;
}

void Timer::restart(Timestamp now)  {
    expiration_ = now;
}


#endif


