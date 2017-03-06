#include "lm_autolock.h"

lm_autolock::lm_autolock(pthread_mutex_t &mutex): m(mutex)
{
    pthread_mutex_lock(&m);
}

lm_autolock::~lm_autolock()
{
    pthread_mutex_unlock(&m);
}
