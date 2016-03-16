/*************************************************************************
    > File Name: Channel.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月16日 星期三 21时10分45秒
 ************************************************************************/
#ifndef _CHANNEL_CPP_
#define _CHANNEL_CPP_

#include"Channel.h"

using namespace NetworkLib;

void Channel::handleEvent(Timestamp reciveTime)  {
    MutexLockGuarnd mutex(lock_);
    handleEventWithGuard(reciveTime);
}

void Channel::handleEventWithGuard(Timestamp reciveTime) {
    if((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))  {
        if(closeCallBack_)  closeCallBack_();
    }
    if(revents_ & (EPOLLERR | EPOLLNVAL)) {
        if(errorCallBack_)  errorCallBack_();
    }
    if(revents_ & (EPOLLIN | EPOLLPRI | EPOLLHUP)) {
        if(readCallBack_)  readCallBack_();
    }
    if(revents_ & EPOLLOUT)  {
        if(writeCallBack_)  writeCallBack_();
    }
}


#endif
