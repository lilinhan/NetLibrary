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

Epoll::Epoll(int size):size_(size){
    assert(size >= 0);
    epollFd_ = epoll_create(epollSize_);
}

Epoll::~Epoll() {
    close(epollFd_);
}

void Epoll::ctrlEvent(int op, int fd, uint32_t event) {
    ev_.data.fd = fd;
    ev_.events = event;
    epoll_ctl(epollFd_, op, fd, &ev_);
}

int Epoll::Poll(int timeout)  {
    return epoll_wait(epollFd_, events_.get(), size_, timeout);
}

EVENT Epoll::getEvents() {
    return events_;
}

#endif
