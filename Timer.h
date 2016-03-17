/*************************************************************************
    > File Name: Timer.h
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月05日 星期六 13时15分32秒
 ************************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_

#pragma once

#include<iostream>
#include<functional>
#include<thread>

#include<signal.h>
#include<sys/time.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

#include"Timestamp.h"

namespace NetworkLib {
    class Timestamp;

    typedef std::function<void()> TimerCallBack;

    class Timer: {
        public:
            Timer(const TimerCallBack &cb, Timestamp when, double interval);
            ~Timer() {}

            void run() const;
            Timestamp getExpiration() const;
            bool ifRepeat() const;
            void restart(Timestamp now);

        private:
            const TimerCallBack CallBack_;
            //time left
            Timestamp expiraton_;
            const double interval_;
            const bool repeat_;
    };
}

#endif
