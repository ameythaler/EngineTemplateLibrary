#include "Threading/ScopeLock.h"
#include "Threading/Lockable.h"

namespace ETL
{
namespace Threading
{
	ScopeReadLock::ScopeReadLock(ILockable& lockable) : m_Lockable(lockable)
	{
		m_Lockable.LockRead();
	}

	ScopeReadLock::~ScopeReadLock()
	{
		m_Lockable.UnlockRead();
	}

	ScopeWriteLock::ScopeWriteLock(ILockable& lockable) : m_Lockable(lockable)
	{
		m_Lockable.LockWrite();
	}

	ScopeWriteLock::~ScopeWriteLock()
	{
		m_Lockable.UnlockWrite();
	}
}
}