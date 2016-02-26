/*************************************************************************
    > File Name: UDP.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年02月21日 星期日 17时08分55秒
 ************************************************************************/
#ifndef _UDP_CPP_
#define _UDP_CPP_

#include"Socket.h"

namespace Socket {
    UDP::UDP(void):BaseSocket(SOCK_DGRAM) {}

    UDP::UDP(const UDP &udp):BaseSocket() {
        this->_socket_id = udp._socket_id;
        this->_opened = udp._opened;
        this->_binded = udp._binded;
    }

    template<class T>
    int UDP::send(IP ip, PORT port, const T* data, size_t len)  {
        if(!this->_opened) this->open();

        len *= sizeof(T);
        if(len > (SOCKET_MAX_BUFFER_LEN * sizeof(T))) {
            std::stringstream error;
            error << "[send] with [ip = " << ip << "][port = " << port <<"][data = "<< data <<"][len = "<< len <<"]Data length higher than max buffer length";
            throw SocketException(error.str());
        }

        Address address(ip, port);
        int ret;

        if((ret = sendto(this->_socket_id, (const char *)data, len, 0, (struct sockaddr*)&address, sizeof(struct sockaddr))) == -1) {
            std::stringstream error;
            error << "[send] with [ip = "<< ip << "][port = " << port << "][data = " << data << "][len = "<< len << "]Cannot send";
            throw SocketException(error.str());
        }

        return ret;
    }

    template<class T>
    int UDP::send(Address address, const T* data, size_t len) {
        return this->send<T>(address.ip(), address.port(), data, len);
    }

    template<class T>
    int UDP::send(IP ip, PORT port, T data) {
        return this->send<T>(ip, port, &data, 1);
    }

    template<class T>
    int UDP::send(Address address, T data) {
        return this->send<T>(address.ip(), address.port(), &data , 1);
    }

    template<>
    int UDP::send<std::string>(IP ip, PORT port, std::string data) {
        return this->send<char>(ip, port, data.c_str(), data.length() + 1);
    }

    template<>
    int UDP::send<std::string>(Address address, std::string data) {
        return this->send<char>(address.ip(), address.port(), data.c_str(), data.length() + 1);
    }

    template<class T>
    int UDP::send(IP ip, PORT port, std::vector<T> data) {
        return this->send<T>(ip, port, data.data(), data.size());
    }

    template<class T>
    int UDP::send(Address address, std::vector<T> data) {
        return this->send<T>(address.ip(), address.port(), data.data(), data.size());
    }

    template<class T>
    int UDP::receive(Socket::Address *address, T *data, size_t len, unsigned int *receive_elements) {
        if(!this->_opened) this->open();
        if(!this->_binded) throw SocketException("[receive]Make the socket listening before recriving");

        len *= sizeof(T);
        if(len > (SOCKET_MAX_BUFFER_LEN * sizeof(T))) {
            std::stringstream error;
            error << "[send]with [buffer = "<< data <<"][len = "<< len << "]Data length higher than max length";
            throw SocketException(error.str());
        }

        int receive_bytes;
        socklen_t size = sizeof(struct sockaddr);

        if((receive_bytes = recvfrom(this->_socket_id, (char *)data, len, 0, (struct sockaddr*)address, (socklen_t*)&size)) == -1) {
            throw SocketException("[receive]Cannot receive");
        }

        *receive_elements = (unsigned int)(receive_bytes / sizeof(T));

        return receive_bytes;
    }

    template<class T>
    DataGram<T*> UDP::receive(T *_buffer, size_t len) {
        len = SOCKET_MAX_BUFFER_LEN;
        DataGram<T*> ret;
        ret._receive_bytes = this->receive<T>(&ret._address, _buffer, len, &ret._receive_elements);

        ret.data = _buffer;
        return ret;
    }

    template<class T, size_t N>
    DataGram<T[N]> UDP::receive(size_t len) {
        len = N;
        DataGram<T[N]> ret;
        ret._receive_bytes = this->receive<T>(&ret._address, ret._data, len, &ret._receive_elements);
        return ret;
    }

    template<class T>
    DataGram<T> UDP::receive(void) {
        DataGram<T> ret;
        ret._receive_bytes = this->receive<T>(&ret._address, &ret._data, 1, &ret._receive_elements);
        return ret;
    }

    template<>
    DataGram<std::string> UDP::receive<std::string>(void)  {
        DataGram<std::string> ret;
        char buffer[SOCKET_MAX_BUFFER_LEN];

        ret._receive_byte = this->receive<char>(&ret._address, buffer, SOCKET_MAX_BUFFER_LEN, &ret._receive_elements);
        ret._data = buffer;

        return ret;
    }

    template<class T>
    DataGram<std::vector<T> > UDP::receive(size_t len) {
        DataGram<std::vector<T> > ret;
        T buffer[len];

        ret._receive_bytes = this->receive<T>(&ret._address, buffer, len, &ret._receive_elements);
        for(int i = 0; i < ret._receive_elements; i++) {
            ret._data.push_back(buffer[i]);
        }
        return ret;
    }
}


#endif
