/*************************************************************************
    > File Name: main.cpp
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年03月05日 星期六 13时32分24秒
 ************************************************************************/
#include"Log.cpp"
#include<thread>

int main(int argc, char *argv[])
{
    NetworkLib::Log log;
    log << std::make_tuple(OFF, "file error", __FILE__, __LINE__);
    return EXIT_SUCCESS;
}

