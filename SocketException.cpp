/*************************************************************************
    > File Name: SocketException.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年02月20日 星期六 15时58分08秒
 ************************************************************************/
#ifndef _SOCKET_EXCEPTION_CPP_
#define _SOCKET_EXCEPTION_CPP_

#include"Socket.h"

namespace Socket{
    SocketException::SocketException(const std::string& message) {
        this->_error = message;
    }

    SocketException::~SocketException() throw(){}

    const char* SocketException::what() const throw() {
        return this->_error.c_str();
    }

    std::ostream& operator<< (std::ostream& out, SocketException &e) {
        out << e.what();
        return out;
    }
}

#endif
