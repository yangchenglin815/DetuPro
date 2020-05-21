#ifndef M1_MUTEX_H
#define M1_MUTEX_H

#include <stdint.h>
#include <pthread.h>

#define SDL_MUTEX_TIMEDOUT  1
#define SDL_MUTEX_MAXWAIT   (~(uint32_t)0)

typedef struct M1_mutex {
    pthread_mutex_t id;
} M1_mutex;

M1_mutex  *M1_CreateMutex(void);
void      M1_DestroyMutex(M1_mutex *mutex);
void      M1_DestroyMutexP(M1_mutex **mutex);
int         M1_LockMutex(M1_mutex *mutex);
int         M1_UnlockMutex(M1_mutex *mutex);

typedef struct M1_cond {
    pthread_cond_t id;
} M1_cond;

M1_cond   *M1_CreateCond(void);
void       M1_DestroyCond(M1_cond *cond);
void       M1_DestroyCondP(M1_cond **mutex);
int          M1_CondSignal(M1_cond *cond);
int          M1_CondBroadcast(M1_cond *cond);
int          M1_CondWait(M1_cond *cond, M1_mutex *mutex);

#endif

