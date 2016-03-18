/*************************************************************************
    > File Name: test.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月18日 星期五 16时24分39秒
 ************************************************************************/
#include"../Net/Socket/Socket.h"

#include<iostream>
int main(int argc, char *argv[])
{
    NetworkLib::Socket::TCP server;
    server.connect_to(NetworkLib::Socket::Address("127.0.0.1", 8000));
    return EXIT_SUCCESS;
}

