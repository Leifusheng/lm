#ifndef __LM_AUTOLOCK__H__
#define __LM_AUTOLOCK__H__
#include <pthread.h>

static void lm_mutex_init(pthread_mutex_t &_mutex)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&_mutex, &attr);
}

class lm_autolock
{
public:
    lm_autolock(pthread_mutex_t& mutex);
    ~lm_autolock();
private:
    pthread_mutex_t& m;
};

#endif
