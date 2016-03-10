/*************************************************************************
  > File Name: Log.cpp
  > Author: lewin
  > Mail: lilinhan1303@gmail.com
  > Organization: Xiyou Linux Group
  > Created Time: 2016年03月06日 星期日 12时50分24秒
 ************************************************************************/
#ifndef _LOG_CPP_
#define _LOG_CPP_

#include"Log.h"

namespace NetworkLib{
    Log::Log() {
        std::ifstream _fin("./config/log.config");   //open config file
        std::string _config_file_contex;        //get config context
        _fin >> _config_file_contex;        //config context to string
        _config_file_contex = _config_file_contex.substr(_config_file_contex.find('=') + 1);  //get context behind operator =
        PATH = _config_file_contex;  //get path

        if(access(PATH.c_str(), F_OK) == -1)  {  //Determined wheather the file exists,Create if not exists
            int _fd = open(PATH.c_str(), O_CREAT | O_EXCL, 0666);
            close(_fd);  //finish create
        }
    }

    Log::~Log() {}

    template<typename T>
        std::string Log::to_string(const T &_t) {
            std::string _result;  //return value
            std::ostringstream _temp;    //temp for exchange format

            _temp << _t;            //exchange by ostring stream
            _result = _temp.str();

            return _result;     //return result
        }

    std::string Log::level_to_string(Level _level) {
        switch(_level) {        //factory function return level string after format
            case Level::OFF : return std::string("OFF"); break;
            case Level::FATAL : return std::string("FATAL"); break;
            case Level::ERROR : return std::string("ERROR"); break;
            case Level::WARN : return std::string("WARN"); break;
            case Level::INFO : return std::string("INFO"); break;
            case Level::DEBUG : return std::string("DEBUG"); break;
            case Level::TRACE : return std::string("TRACE"); break;
            default: return std::string("SHIT"); break;
        }
        return NULL;
    }

    void Log::write_hard_disk() {

    }

    const Log& Log::operator<< (std::tuple<Level, std::string, std::string, int> _tu_data){

        _buffer = _time.now() + end;    //add time stamp to buffer

        pthread_t _id = pthread_self();  //get main thread id
        _buffer = _buffer + to_string(_id) + end;  //add mian thread id to buffer

        _buffer = _buffer + level_to_string(std::get<0>(_tu_data)) + end;  //add level to buffer

        _buffer = _buffer + std::get<1>(_tu_data) + end; //add log context

        _buffer = _buffer + std::get<2>(_tu_data) + end; //add source file name

        _buffer = _buffer + to_string(std::get<3>(_tu_data)); //add line

        _buffer = _buffer + "\n";

        std::cout << _buffer;
        return *this;
    }
}

#endif
