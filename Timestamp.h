/*************************************************************************
    > File Name: Timestap.h
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月04日 星期五 20时43分34秒
 ************************************************************************/
#ifndef _TIMESTAP_H_
#define _TIMESTAP_H_

#include<iostream>
#include"noncopyable.h"
#include<stdio.h>
#include<time.h>
#include<sstream>

#pragma once

namespace NetworkLib{
    class Timestamp :private noncopyable
    {
        private:
            struct tm *_time_struct;
            time_t _temp;
            std::string _year_time;
            std::string _hour_time;

            void timetostring();
            void updatetime();
        public:
            Timestamp(){};
            ~Timestamp(){};
            std::string now();  // get time
            void clear();
    };
}

#endif
