#include "Utility/Platform.h"

#if ETL_MSVC

#include "Threading/SimpleMutex_Msvc.h"

namespace ETL
{
namespace Threading
{
	void SimpleMutex::Lock()
	{
		AcquireSRWLockExclusive(&m_Lock);
	}

	void SimpleMutex::Unlock()
	{
		ReleaseSRWLockExclusive(&m_Lock);
	}
}
}

#endif // ETL_MSVC
