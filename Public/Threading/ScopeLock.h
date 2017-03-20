#pragma once

namespace ETL
{
namespace Threading
{
	class ILockable;

	struct ScopeReadLock
	{
		ScopeReadLock(ILockable& lockable);
		~ScopeReadLock();

	private:
		ILockable& m_Lockable;
	};

	struct ScopeWriteLock
	{
		ScopeWriteLock(ILockable& lockable);
		~ScopeWriteLock();

	private:
		ILockable& m_Lockable;
	};
}
}