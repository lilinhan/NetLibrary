/*************************************************************************
    > File Name: Timestamp.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月04日 星期五 20时53分10秒
 ************************************************************************/
#include"Timestamp.h"

namespace NetworkLib{
    void Timestamp::updatetime()  {
        _temp = time(&_temp);
        _time_struct = gmtime(&_temp);
    }

    void Timestamp::timetostring()  {
        updatetime();
        char buf[20];
        snprintf(buf, 20, "%d年%d月%d日 ",_time_struct->tm_year+1900, _time_struct->tm_mon+1, _time_struct->tm_mday);
        {
            std::string str(buf);
            _year_time += str;
        }

        snprintf(buf, 20, "%d时%d分%d秒",_time_struct->tm_hour, _time_struct->tm_min, _time_struct->tm_sec);
        {
            std::string str(buf);
            _hour_time += str;
        }
    }

    std::string Timestamp::now() {
        timetostring();
        return _year_time + _hour_time;
    }
}

/*
int main(int argc, char *argv[])
{
    NetworkLib::Timestamp t;
    std::cout << t.now() << std::endl;
    return EXIT_SUCCESS;
}
*/
