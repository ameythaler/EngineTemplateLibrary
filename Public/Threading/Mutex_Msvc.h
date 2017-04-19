#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC

#include "Windows.h"
#include "Threading/Lockable.h"
#include "Threading/Synchronizer.h"
#include <atomic>

namespace ETL
{
namespace Threading
{
	class Mutex : public ILockable
	{
	public:
		Mutex();
		virtual void LockRead();
		virtual void LockWrite();
		virtual void UnlockRead();
		virtual void UnlockWrite();
		inline virtual uint32 GetReadLockCount() const { return m_ReadCount; }
		inline virtual bool IsWriteLocked() const { return m_bIsWriteLocked; }

	private:
		SRWLOCK m_WriteLock;
		Synchronizer m_WaitLock;
		std::atomic<uint32> m_ReadCount;
		std::atomic<bool> m_bIsWriteLocked;
	};
}
}

#endif // ETL_MSVC