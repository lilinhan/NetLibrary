/*************************************************************************
    > File Name: Condition.h
    > Author: lewin
    > Mail: lilinhan1303@gmail.com
    > Organization: Xiyou Linux Group
    > Created Time: 2016年02月29日 星期一 14时56分06秒
 ************************************************************************/
#ifndef _CONDITION_H_
#define _CONDITION_H_

#include"noncopyable.h"
#include"Mutex.h"

namespcae NetworkLib{
    class Condition:noncopyable {
        public:
            explicit Condition(Mutex &mutex):_mutex(mutex) {
                pthread_cond_init(&cond, NULL);
            }
            ~Condition() {
                pthread_cond_destroy(&cond);
            }

            void wait() {
                pthread_cond_wait(&cond, _mutex.getmutex());
            }

            bool notify() {
                return pthread_cond_signal(&cond) == 0;
            }

            bool notifyAll() {
                return pthread_cond_broadcast(&cond) == 0;
            }

        private:
            MutexLock &_mutex;
            pthread_cond_t cond;
    };
}

#endif
