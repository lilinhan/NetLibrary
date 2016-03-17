/*************************************************************************
    > File Name: Epoll.h
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月17日 星期四 19时23分20秒
 ************************************************************************/
#ifndef _EPOLL_H_
#define _EPOLL_H_

#include<iostream>
#include<sys/epoll.h>

namespace NetworkLib{
    class Epoll {
        public:
            Epoll(int size);

        private:
            //epoll fd
            int epollFd_;
    }
}

#endif
