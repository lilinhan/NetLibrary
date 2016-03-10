/*************************************************************************
    > File Name: thread.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年01月29日 星期五 09时00分09秒
 ************************************************************************/
#include<iostream>
#include<thread>

#include"Condition.h"
#include"Mutex.h"

const int COUNT = 1000000;

int num = 0;

NetworkLib::MutexLock _mutex;

void fun1() {
    NetworkLib::MutexLockGuarnd lk(_mutex);
    for(int i = 0; i < COUNT; i++)  {
        num++;
    }
}

void fun2() {
    NetworkLib::MutexLockGuarnd lk(_mutex);
    for(int i = 0; i < COUNT; i++)  {
        num++;
    }
}

int main(int argc, char *argv[])
{
    std::thread t1(fun1);
    std::thread t2(fun2);

    t1.join();
    t2.join();

    std::cout << num << std::endl;
    return EXIT_SUCCESS;
}

