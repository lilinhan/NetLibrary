/*************************************************************************
  > File Name: DataGram.cpp
  > Author: lewin
  > Mail: lilinhan1303@gmail.com
  > Organization: Xiyou Linux Group
  > Created Time: 2016年02月21日 星期日 16时20分04秒
 ************************************************************************/
#ifndef _DATAGRAM_CPP_
#define _DATAGRAM_CPP_

#include"Socket.h"

namespace NetworkLib{
    namespace Socket {
        template<class Datatype>
            template<class T>
            void DataGram<Datatype>::operator= (const DataGram<T> &datagram)  {
                this->_address = datagram._address;
                this->_data = datagram._data;
            }
    }
}

#endif
