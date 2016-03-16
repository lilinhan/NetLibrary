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
    if((revents_ & POLLHUP) && !(revents_ & POLLIN))  {
        if(closeCallBack_)  closeCallBack_();
    }
    if(revents_ & (POLLERR | POLLNVAL)) {
        if(errorCallBack_)  errorCallBack_();
    }
    if(revents_ & (POLLIN | POLLPRI | POLLHUP)) {
        if(readCallBack_)  readCallBack_();
    }
    if(revents_ & POLLOUT)  {
        if(writeCallBack_)  writeCallBack_();
    }
}


#endif
