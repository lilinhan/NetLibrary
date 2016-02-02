/*************************************************************************
    > File Name: ThreadPool.h
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年02月01日 星期一 15时46分30秒
 ************************************************************************/
#pragma once

#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<mutex>
#include<thread>
#include<condition_variable>

#include<assert.h>

#include"noncopyable.h"

namespace NetworkLib{
    class ThreadPool:private noncopyable
    {
        private:
            bool stop_;  //1:stop 0:run
            std::vector<std::thread>  Works_;   //threads
            std::queue<std::function<void()>> Tasks_;  //The task queue
            //synchronization
            std::mutex TasksMutex_; //Mutex for task queue
            std::condition_variable Condition_;

            void Invoke(); //Threads invoke Functions
        public:
            ThreadPool(int ThreadsNum); //init the ThreadPool
            ~ThreadPool();

            //put function in task queue
            void Enqueue(std::function<void ()> f);

            //close the thread pool
            void ShutDown();
    };
};


