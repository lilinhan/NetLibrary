/*************************************************************************
    > File Name: Log.h
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月06日 星期日 10时00分49秒
 ************************************************************************/
#ifndef _LOG_H_
#define _LOG_H_

#include<iostream>
#include<mutex>
#include<ctime>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<cstdio>
#include<sys/types.h>
#include<unistd.h>
#include<thread>
#include<condition_variable>
#include<fstream>
#include<pthread.h>
#include<sstream>
#include<tuple>

#include"Timestamp.cpp"
#include"Mutex.h"

enum Level{
    OFF,    //The highest level, close log
    FATAL,  //Serious error
    ERROR,  //error
    WARN,   //warning
    INFO,   //information
    DEBUG,  //debug
    TRACE,  //trace process
};

namespace NetworkLib{
    class Log{
        private:
            Timestamp _time;  //get time stamp
            std::thread _back_thread;   //backthread  write buffer to hard disk
            std::condition_variable _buffer_empty;   //judge the buffer empty
            std::condition_variable _buffer_full;   //judge the buffer full

            std::string _buffer;   //main thread write in buffer, Log's thread write to hard disk
            std::string PATH;  //Log file name  you want. in ./config/log.config

            std::string end = "  "; // for format buffer

            void write_hard_disk();  //Log's thread use

            template<typename T>
            std::string to_string(const T &t);  //format all type to string

            std::string level_to_string(Level _level);  //Level exchange to string

        public:
            Log();  //default
            ~Log();

            const Log& operator<< (std::tuple<Level, std::string, std::string, int>);  //easy to build log
    };
}

#endif
