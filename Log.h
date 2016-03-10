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
#include<chrono>
#include<fstream>
#include<vector>

#include"Timestamp.cpp"

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
            std::condition_variable _buffer_full;   //judge the buffer full
            std::mutex _mutex;  //lock the _buffer
 //            std::string _buffer;   //main thread write in buffer, Log's thread write to hard disk
            std::string PATH;  //Log file name  you want. in ./config/log.config
            std::string end = "  "; // for format buffer
            bool _start;    //Log system start

            std::shared_ptr<std::thread> ptr;  //thread point

            void write_hard_disk();  //Log's thread use
            template<typename T>
            std::string to_string(const T &t);  //format all type to string
            std::string level_to_string(Level _level);  //Level exchange to string

            std::vector<std::string> _all_logs;  //all logs
        public:
            Log();  //default
            ~Log();

            void start_log(); //start log system for user

            void stop_log();  //stop log system for user

            const Log& operator<< (std::tuple<Level, std::string, std::string, int>);  //easy to build log
    };
}

#endif
