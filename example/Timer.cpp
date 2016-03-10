/*************************************************************************
    > File Name: main.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月05日 星期六 13时32分24秒
 ************************************************************************/
#include<iostream>
#include"../Time.cpp"

#include<unistd.h>
#include<stdlib.h>

void print(int a) {
    std::cout << "hello world!" << std::endl;
}

int main(int argc, char *argv[])
{
    NetworkLib::Timer t;
    t.set_task(print, 5);

    for(int i = 0; i < 20 ; i++) {
        std::cout << "num = " << i << std::endl;
        sleep(1);
    }

    return EXIT_SUCCESS;
}

