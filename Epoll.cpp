/*************************************************************************
    > File Name: Epoll.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月17日 星期四 19时29分12秒
 ************************************************************************/
#ifndef _EPOLL_CPP_
#define _EPOLL_CPP_

#include"Epoll.h"

using namespace NetworkLib;

Epoll::Epoll(itn size){
    epollFd_ = epoll_create(epollSize_);
}



#endif
