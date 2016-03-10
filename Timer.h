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

#include"noncopyable.h"

namespace NetworkLib {
    class Timer:noncopyable {
        private:
            unsigned int time;

        public:
            Timer() {}
            ~Timer() {}

            void set_task(void (*p)(int), unsigned int t); //add time task
    };
}

#endif
