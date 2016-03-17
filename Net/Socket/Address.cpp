/*************************************************************************
  > File Name: Address.cpp
  > Author: lewin
  > Mail: lilinhan1303@gmail.com
  > Organization: Xiyou Linux Group
  > Created Time: 2016年02月20日 星期六 16时04分15秒
 ************************************************************************/
#ifndef _ADDRESS_CPP_
#define _ADDRESS_CPP_

#include"Socket.h"
namespace NetworkLib{
    namespace Socket {
        void Address::address(IP ip, PORT port) {
            this->sin_family = AF_INET;
            this->ip(ip);
            this->port(port);
        }

        Address::Address() {
            address("0.0.0.0", 0);
        }

        Address::Address(PORT port) {
            address("0.0.0.0", port);
        }

        Address::Address(IP ip, PORT port) {
            address(ip, port);
        }

        Address::Address(struct sockaddr_in address) {
            this->address(inet_ntoa(address.sin_addr),address.sin_port);
        }

        Address::Address(const Address& address) {
            this->sin_family = address.sin_family;
            this->sin_addr = address.sin_addr;
            this->sin_port = address.sin_port;
        }

        IP Address::ip(void) {
            return inet_ntoa(this->sin_addr);
        }

        IP Address::ip(IP ip) {
            if(inet_aton(ip.c_str(), &this->sin_addr) == 0) {
                std::stringstream error;
                error << "[ip] with [ip = "<< ip <<"] invalid ip address provided";
                throw SocketException(error.str());
            }
            return this->ip();
        }

        PORT Address::port(void) {
            return ntohs(this->sin_port);
        }

        PORT Address::port(PORT port) {
            this->sin_port = htons(port);
            return this->port();
        }

        std::ostream& operator<< (std::ostream& out, Address& address) {
            out << address.ip() << "." << address.port();
            return out;
        }
    }
}

#endif
