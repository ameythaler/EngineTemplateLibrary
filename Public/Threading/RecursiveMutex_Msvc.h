#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC

#include "Windows.h"
#include <atomic>
#include "Threading/Lockable.h"
#include "Threading/Synchronizer.h"

namespace ETL
{
namespace Threading
{
	class RecursiveMutex : public ILockable
	{
	public:
		RecursiveMutex();
		virtual void LockRead();
		virtual void LockWrite();
		virtual void UnlockRead();
		virtual void UnlockWrite();
		inline virtual uint32_t GetReadLockCount() const { return m_ReadCount; }
		inline virtual bool IsWriteLocked() const { return m_WriteLockCount > 0; }

	private:
		CRITICAL_SECTION m_WriteLock;
		Synchronizer m_WaitLock;
		std::atomic<uint32_t> m_ReadCount;
		std::atomic<uint32_t> m_WriteLockCount;
	};
}
}

#endif // ETL_MSVC