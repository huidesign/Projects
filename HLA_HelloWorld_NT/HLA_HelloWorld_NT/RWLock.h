/************************************************************************/
/* RWLock.h: interface for the RWLock class.                            */
/************************************************************************/

#if _MSC_VER > 1000
#pragma once
#endif	//_MSC_VER > 1000

#if !defined(AFX_RWLOCK_H__FC1FBC77_A4DE_4C40_B67A_4534791A349F__INCLUDED_)
#define AFX_RWLOCK_H__FC1FBC77_A4DE_4C40_B67A_4534791A349F__INCLUDED_

#include <Windows.h>
#define USE_CRITICAL_SECTION

class RWLock
{
public:
	RWLock();
	virtual ~RWLock();
public:
	/************************************************************************/
	/* Concrete implementation may be modified, but the public interface    */
	/* will need no change                                                  */
	/************************************************************************/
	// get lock to write
	BOOL getWriteLock();
	// end write and release the lock
	BOOL releaseWriteLock();

	// get lock to read
	BOOL getReadLock();
	// end read and release the lock
	BOOL releaseReadLock();

	// check whether write ok
	BOOL isWriteOK();
	// check whether read ok
	BOOL isReadOK();
private:
#ifdef USE_CRITICAL_SECTION
	// the most simple method
	CRITICAL_SECTION m_criticalSection;
#else
	HANDLE m_hMutex;
#endif
};	// end RWLock

#endif	// !defined(AFX_RWLOCK_H__FC1FBC77_A4DE_4C40_B67A_4534791A349F__INCLUDED_)