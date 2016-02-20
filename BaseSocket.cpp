/*************************************************************************
    > File Name: BaseSocket.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年02月20日 星期六 15时13分41秒
 ************************************************************************/
#ifndef _BASE_SOCKET_CPP_
#define _BASE_SOCKET_CPP_

#include"Socket.h"

namespace Socket{
    BaseSocket::BaseSocket(int socket_type) {
        this->_socket_type = socket_type;
        this->_opened = false;
        this->_binded = false;
        this->open();
    }

    BaseSocket::~BaseSocket() {}

    void BaseSocket::open(void) {
        if(!this->_open) {
            if((this->_socket_id = socket(AF_INET, this->_socket_type, 0)) == -1)
                throw SocketException("[open] Cannot create socket");
            this->_opened = true;
            this->_binded = false;
        }
    }

    void BaseSocket::close(void) {
        if(this->_opened) {
            shutdown(this->_socket_id, SHTU_RDWR);
        }
        this->_opened = false;
        this->_binded = false;
    }

    void BaseSocket::listen_on_port(PORT port) {
        if(this->_binded) {
            throw SocketException("[listen_on_port]Socket already binded to a port");
        }
        if(!this->_opened)  {
            this->open();
        }

        Address address(port);

        if(bind(this->_socket_id, (struct sockaddr*)&address, sizeof(struct sockaddr)) == -1) {
            std::stringstream error;
            error << "[listen_on_port]with [port = "<< port <<"]Cannot bind socket";
            throw SocketException(error.str());
        }

        this->_binded = true;
    }
}

#endif
