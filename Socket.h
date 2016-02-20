/*************************************************************************
    > File Name: Socket.h
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年02月19日 星期五 09时29分16秒
 ************************************************************************/
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include<iostream>
#include<sstream>
#include<exception>
#include<string>
#include<vector>
#include<fstream>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

#define SOCKET_MAX_BUFFER_LEN 1024

namespace Socket
{
    typedef int SOCKETID;
    typedef std::string IP;
    typedef unsigned int PORT;

    class SocketException : public std::exception {
        private:
            std::string _error;

        public:
            SocketException(const std::string&);
            ~SocketException() throw();

            virtual const char* what() const throw();       //get error
            friend std::ostream& operator<< (std::ostream& out, SocketException &e);  //print error to the screen
    };

    class Address : protected sockaddr_in {
        private:
            void address(IP, PORT);

        public:
            Address();
            Address(PORT);
            Address(IP, PORT);
            Address(struct sockaddr_in);
            Address(const Address&);

            IP ip(void);
            IP ip(IP);

            PORT port(void);
            PORT port(PORT);

            friend std::ostream& operator<< (std::ostream& ,Address &);
    };

    template<class DataType>
        class DataGram {
            public:
                Address _address;
                DataType _data;
                unsigned int _receive_byte;
                unsigned int _receive_elements;

                template<class T>
                    void operator= (const DataGram<T>&);
        };

    class BaseSocket{
        protected:
            SOCKETID _socket_id;
            int _socket_type;
            bool _opened;
            bool _binded;

        public:
            BaseSocket(int);
            ~BaseSocket();

            void open(void);
            void close(void);

            virtual void listen_on_port(PORT);
    };

    class UDP : public BaseSocket {
        public:
            UDP(void);
            UDP(const UDP&);

            template<class T> int send(IP, PORT, const T*, size_t);
            template<class T> int send(Address, const T*, size_t);
            template<class T> int send(IP, PORT, T);
            template<class T> int send(Address, T);
            template<class T> int send(IP, PORT, std::vector<T>);
            template<class T> int send(Address, std::vector<T>);

            template<class T> int receive(Address*, T*, size_t, unsigned int);
            template<class T> DataGram<T*> receive(T*, size_t);
            template<class T, size_t N> DataGram<T[N]> receive(size_t);
            template<class T> DataGram<T> receive(void);
            template<class T> DataGram<std::vector<T>> receive(size_t);
    };

    class TCP : public BaseSocket {
        private:
            Address _address;

        public:
            TCP(void);
            TCP(const TCP&);

            IP ip(void);
            IP PORT(void);
            Address address(void);

            void listen_on_port(Socket::PORT);
            void connect_to(Address);

            TCP accept_client(void);
            template<class T> int send(const T*, size_t);
            template<class T> int receive(T*, size_t);

            void send_file();
            void receive_file();
    };
}

#endif
