/*************************************************************************
  > File Name: ThreadPool.cpp
  > Author: lewin
  > Mail: lilinhan1303@gmail.com
  > Organization: Xiyou Linux Group
  > Created Time: 2016年02月02日 星期二 11时56分54秒
 ************************************************************************/
#include"ThreadPool.h"
#include<unistd.h>

namespace NetworkLib{

ThreadPool::ThreadPool(int ThreadNum):stop_(false) {
    for(int i = 0; i < ThreadNum; i++) {
        Works_.emplace_back(std::thread(&ThreadPool::Invoke, this));
    }
}

ThreadPool::~ThreadPool() {
    if(!stop_) {
        ShutDown();
    }
}

void ThreadPool::Enqueue(std::function<void()> f) {
    {
        std::unique_lock<std::mutex> lock(TasksMutex_);
        Tasks_.push(f);
    }
    Condition_.notify_one();
}

void ThreadPool::ShutDown() {
        Condition_.notify_all();
        for(std::thread &thread:Works_) {
            thread.join();
        }
        stop_ = true;
}

void ThreadPool::Invoke() {
    std::function<void()> fun;
    {
        std::unique_lock<std::mutex> lock(TasksMutex_);
        Condition_.wait(lock, [this]{ return !stop_ || !Tasks_.empty() ;});
        if( Tasks_.empty() || stop_ ) {
            return;
        }
        fun = Tasks_.front();

        Tasks_.pop();
    }
    fun();
}
}


