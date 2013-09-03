#include "RWLock.h"

/************************************************************************/
/* Construction/Destruction                                             */
/************************************************************************/

RWLock::RWLock()
{
#ifdef USE_CRITICAL_SECTION
	InitializeCriticalSection(&m_criticalSection);
#else
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
	if (m_hMutex == NULL)
		printf("Create mutex failed, code is %d", GetLastError());
#endif
}

RWLock::~RWLock()
{
#ifdef USE_CRITICAL_SECTION
	DeleteCriticalSection(&m_criticalSection);
#else
	if(m_hMutex)
		CloseHandle(m_hMutex);
#endif
}

/************************************************************************/
/* Implement of member function, concrete implementation may be modified*/
/************************************************************************/

BOOL RWLock::getWriteLock()
{
#ifdef USE_CRITICAL_SECTION
	EnterCriticalSection(&m_criticalSection);
#else
	WaitForSingleObject(m_hMutex, 99999);
#endif
	return TRUE;
}

BOOL RWLock::releaseWriteLock()
{
#ifdef USE_CRITICAL_SECTION
	LeaveCriticalSection(&m_criticalSection);
#else
	if (ReleaseMutex(m_hMutex) == FALSE)
		printf("release mutex failed, code is: %d", GetLastError());
#endif
	return TRUE;
}

BOOL RWLock::getReadLock()
{
#ifdef USE_CRITICAL_SECTION
	EnterCriticalSection(&m_criticalSection);
#else
	WaitForSingleObject(m_hMutex, 99999);
#endif
	return TRUE;
}

BOOL RWLock::releaseReadLock()
{
#ifdef USE_CRITICAL_SECTION
	LeaveCriticalSection(&m_criticalSection);
#else
	if (ReleaseMutex(m_hMutex) == FALSE)
		printf("release mutex failed, code is: %d", GetLastError());
#endif
	return TRUE;
}

BOOL RWLock::isWriteOK()
{
	// CRITICAL_SECTION NOT SUPPORT
	return FALSE;
}

BOOL RWLock::isReadOK()
{
	// CRITICAL_SECTION NOT SUPPORT
	return FALSE;
}