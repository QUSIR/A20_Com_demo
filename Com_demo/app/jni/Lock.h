#pragma once

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
	#define MUTEX_TYPE CRITICAL_SECTION
	#define MUTEX_INIT(mutex) InitializeCriticalSection(mutex)
	#define MUTEX_DESTROY DeleteCriticalSection
	#define MUTEX_LOCK EnterCriticalSection
	#define MUTEX_UNLOCK LeaveCriticalSection
#else
	#include <pthread.h>
	#define MUTEX_TYPE pthread_mutex_t
	#define MUTEX_INIT(mutex) pthread_mutex_init(mutex,NULL)
	#define MUTEX_DESTROY pthread_mutex_destroy
	#define MUTEX_LOCK pthread_mutex_lock
	#define MUTEX_UNLOCK pthread_mutex_unlock
	
#endif

class Lock {
public:
	Lock(void);
	~Lock(void);
	void lock();
	void unlock();
private:
	MUTEX_TYPE m_lock;
};
