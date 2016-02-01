/*************************************************************************
    > File Name: noncopyable.h
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年02月01日 星期一 15时10分43秒
 ************************************************************************/

#ifndef NETWORKLIB_NONCOPYABLE_H
#define NETWORKLIB_NONCOPYABLE_H

/*
 *别的类继承noncopyable类来实现禁止复制的功能
 */


namespace NetworkLib{
    class noncopyable{
        protected:
            //默认的析构函数和构造函数是保护的
            //default 让编译器自动产生
            noncopyable() = default;
            ~noncopyable() = default;
            //delete禁止编译器自动产生
            noncopyable(const noncopyable&) = delete;
            const noncopyable& operator=(const noncopyable &) = delete;
    }
};
