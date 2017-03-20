#pragma once

#include "Utility/Types.h"

namespace ETL
{
namespace Threading
{
	class ILockable
	{
	public:
		virtual void LockRead() = 0;
		virtual void LockWrite() = 0;
		virtual void UnlockRead() = 0;
		virtual void UnlockWrite() = 0;
		virtual uint32 GetReadLockCount() const = 0;
		virtual bool IsWriteLocked() const = 0;
	};
}
}