#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include "m1_mutex.h"

M1_mutex *M1_CreateMutex(void)
{
	M1_mutex *mutex;
	mutex = (M1_mutex *)malloc(sizeof(M1_mutex));
    if (!mutex)
        return NULL;
	memset(mutex, 0, sizeof(M1_mutex));

    if (pthread_mutex_init(&mutex->id, NULL) != 0) {
        free(mutex);
        return NULL;
    }

    return mutex;
}

void M1_DestroyMutex(M1_mutex *mutex)
{
    if (mutex) {
        pthread_mutex_destroy(&mutex->id);
        free(mutex);
    }
}

void M1_DestroyMutexP(M1_mutex **mutex)
{
    if (mutex) {
        M1_DestroyMutex(*mutex);
        *mutex = NULL;
    }
}

int M1_LockMutex(M1_mutex *mutex)
{
    assert(mutex);
    if (!mutex)
        return -1;

    return pthread_mutex_lock(&mutex->id);
}

int M1_UnlockMutex(M1_mutex *mutex)
{
    assert(mutex);
    if (!mutex)
        return -1;

    return pthread_mutex_unlock(&mutex->id);
}

M1_cond *M1_CreateCond(void)
{
	M1_cond *cond;
	cond = (M1_cond *)malloc(sizeof(M1_cond));
    if (!cond)
        return NULL;
	memset(cond, 0, sizeof(M1_cond));

    if (pthread_cond_init(&cond->id, NULL) != 0) {
        free(cond);
        return NULL;
    }

    return cond;
}

void M1_DestroyCond(M1_cond *cond)
{
    if (cond) {
        pthread_cond_destroy(&cond->id);
        free(cond);
    }
}

void M1_DestroyCondP(M1_cond **cond)
{

    if (cond) {
        M1_DestroyCond(*cond);
        *cond = NULL;
    }
}

int M1_CondSignal(M1_cond *cond)
{
    assert(cond);
    if (!cond)
        return -1;

    return pthread_cond_signal(&cond->id);
}

int M1_CondBroadcast(M1_cond *cond)
{
    assert(cond);
    if (!cond)
        return -1;

    return pthread_cond_broadcast(&cond->id);
}

int M1_CondWait(M1_cond *cond, M1_mutex *mutex)
{
    assert(cond);
    assert(mutex);
    if (!cond || !mutex)
        return -1;

    return pthread_cond_wait(&cond->id, &mutex->id);
}
