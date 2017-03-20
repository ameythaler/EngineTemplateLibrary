#include "Threading/SimpleMutex.h"

namespace ETL
{
namespace Threading
{
	SimpleScopeLock::SimpleScopeLock(SimpleMutex& simpleMutex) : m_Mutex(simpleMutex)
	{
		m_Mutex.Lock();
	}

	SimpleScopeLock::~SimpleScopeLock()
	{
		m_Mutex.Unlock();
	}
}
}