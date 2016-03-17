/*************************************************************************
  > File Name: TCP.cpp
  > Author: lewin
  > Mail: lilinhan1303@gmail.com
  > Organization: Xiyou Linux Group
  > Created Time: 2016年02月26日 星期五 16时08分03秒
 ************************************************************************/
#ifndef _TCP_CPP_
#define _TCP_CPP_

#include"Socket.h"

namespace NetworkLib{
    namespace Socket{
        TCP::TCP(void):BaseSocket(SOCK_STREAM) {}

        TCP::TCP(const TCP &tcp):BaseSocket() {
            this->_socket_id = tcp._socket_id;
            this->_opened = tcp._opened;
            this->_binded = tcp._binded;
        }

        IP TCP::ip(void) {
            return this->_address.ip();
        }

        PORT TCP::port(void) {
            return this->_address.port();
        }

        Address TCP::address(void) {
            return Address(this->_address);
        }

        void TCP::listen_on_port(PORT port, unsigned int listener = 1) {
            BaseSocket::listen_on_port(port);

            if(listen(this->_socket_id, listener) != 0)  {
                std::stringstream error;
                error<< "[listen_on_port] with [port = "<< port << "][listener = "<< listener << "]Cannot bind Socket";
                throw SocketException(error.str());
            }
        }

        void TCP::connect_to(Address address) {
            if(this->_binded) throw SocketException("[connect_to]Socket already binded to a port, use another socket");

            if(!this->_opened) this->open();

            if(connect(this->_socket_id, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) < 0)  {
                std::stringstream error;
                error << "[connect_to]with[address = "<< address << "]Cannot connect to the specified address";
                throw SocketException(error.str());
            }
        }

        TCP TCP::accept_client(void) {
            TCP ret;
            socklen_t len = sizeof(struct sockaddr_in);

            ret.close();
            ret._socket_id = accept(this->_socket_id, (struct sockaddr*)&ret._address, &len);
            ret._opened = true;
            ret._binded = true;
        }

        template<class T>
            int TCP::send(const T* buffer, size_t len) {
                if(!this->_binded) throw SocketException("[send]Socket not binded");
                if(!this->_opened) throw SocketException("[send]Socket not opened");

                len *= sizeof(T);
                if(len > (SOCKET_MAX_BUFFER_LEN * sizeof(T))) {
                    std::stringstream error;
                    error<<"[send][len = "<< len << "]Data length higher than max buffer len("<<SOCKET_MAX_BUFFER_LEN <<")";
                    throw SocketException(error.str());
                }

                int ret;
                if((ret = ::send(this->_socket_id, (const char *)buffer, len, 0)) == -1) {
                    throw SocketException("[send]Cannot send");
                }
                return ret;
            }

        template<class T>
            int TCP::receive(T *buffer, size_t len) {
                if(!this->_binded) throw SocketException("[send_file]Socket not binded");
                if(!this->_opened) throw SocketException("[send_file]Socket not opened");

                len *= sizeof(T);
                if(len > (SOCKET_MAX_BUFFER_LEN * sizeof(T))) {
                    std::stringstream error;
                    error << "[receive][len = "<< len << "]Data length higher than max buffer len("<< SOCKET_MAX_BUFFER_LEN <<")";
                    throw SocketException(error.str());
                }

                int ret;
                if((ret = recv(this->_socket_id, buffer, len ,0)) == -1) {
                    throw SocketException("[send]Cannot receive");
                }
                return ret;
            }

        void TCP::send_file(std::string file_name) {
            unsigned long long file_size;
            char chunk[SOCKET_MAX_BUFFER_LEN];
            char sync;
            std::fstream fp(file_name.c_str(), std::ios::in | std::ios::binary);

            if(!fp.is_open()) {
                std::stringstream error;
                error << "[send_file]with[filename = "<< file_name << "]Cannot open the file";
                throw SocketException(error.str());
            }

            fp.seekg(0, std::ifstream::end);
            file_size = fp.tellg();
            fp.seekg(0, std::ifstream::beg);

            this->send<unsigned long long>(&file_size, 1);

            for(unsigned long long i = 0; i < file_size / SOCKET_MAX_BUFFER_LEN; i++) {
                this->receive<char>(&sync, 1);
                fp.read(chunk, SOCKET_MAX_BUFFER_LEN);
                this->send<char>(chunk, SOCKET_MAX_BUFFER_LEN);
            }

            if((file_size % SOCKET_MAX_BUFFER_LEN) != 0) {
                this->receive<char>(&sync, 1);
                fp.read(chunk, file_size % SOCKET_MAX_BUFFER_LEN);
                this->send<char>(chunk, file_size % SOCKET_MAX_BUFFER_LEN);
            }
            fp.close();
        }

        void TCP::receive_file(std::string file_name) {
            unsigned long long file_size;
            char chunk[SOCKET_MAX_BUFFER_LEN];
            char sync;
            std::fstream fp(file_name.c_str(), std::ios::out | std::ios::binary);

            if(!fp.is_open()) {
                std::stringstream error;
                error << "[receive_file]with[filename = "<< file_name << "]Cannot open the file";
                throw SocketException(error.str());
            }

            this->receive<unsigned long long>(&file_size, 1);

            for(unsigned long long i = 0; i < file_size / SOCKET_MAX_BUFFER_LEN; i++) {
                this->send<char>(&sync, 1);
                this->receive<char>(chunk, SOCKET_MAX_BUFFER_LEN);
                fp.write(chunk, SOCKET_MAX_BUFFER_LEN);
            }

            if((file_size % SOCKET_MAX_BUFFER_LEN) != 0)  {
                this->send<char>(&sync, 1);
                this->send<char>(chunk,file_size % SOCKET_MAX_BUFFER_LEN);
                fp.write(chunk, SOCKET_MAX_BUFFER_LEN);
            }

            fp.close();
        }
    }
}
#endif
