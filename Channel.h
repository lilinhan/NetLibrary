/*************************************************************************
    > File Name: Channel.h
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月16日 星期三 19时06分05秒
 ************************************************************************/
#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include<iostream>
#include<function>
#include<string>
#include<mutex>

#include"Timestamp.h"
#include"Mutex.h"

namespace NetworkLib {
    class Log;
    class Channel {
        public:
            typedef std::function<void()> EventCallBack;
            typedef std::function<void(Timestamp)> ReadEventCallBack;

            Channel();
            ~Channel();

            //handle the event
            void handleEvent(Timestamp receiveTime);
            //set events
            void setReadEvent(const ReadEventCallBack &cd) {readCallBack_ = cb;}
            void setWriteEvent(const EventCallBack &cb) {writeCallBack_ = cb;}
            void setErrorEvent(const EventCallBack &cb) {errorCallBack_ = cb;}
            void setCloseEvent(const EventCallBack &cb) {closeCallBack_ = cb;}

        private:
            //registered events
            int events_;
            //read events
            int revents_;

            //buffer for read or write
            std::string buffer_;

            //handle event in guard
            void handleEventWithGuard(Timestamp receiveTime);

            //mutex
            MutexLock lock_;

            //function for handle
            ReadEventCallBack readCallBack_;
            EventCallBack writeCallBack_;
            EventCallBack errorCallBack_;
            EventCallBack closeCallBack_;
    };
}

#endif

