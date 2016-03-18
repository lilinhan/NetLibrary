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
#include<assert.h>
#include<vector>

namespace NetworkLib{
    using std::shared_ptr<std::vector<epoll_event>> EVENT;
    class Epoll {
        public:
            Epoll(int size);
            ~Epoll();
            // control event
            void ctrlEvent(int op, int fd, uint32_t event);
            //Poll
            int Poll(int timeout);
            //get the events head point
            EVENT getEvents();

        private:
            int size_;
            //epoll fd
            int epollFd_;
            //all events (point)
            EVENT events_;
            //registered event
            struct epoll_event ev_;
    }
}

#endif
