#include "Memory/MemTrack.h"
namespace ETL
{
namespace Memory
{
	template<typename T>
	MemPool<T>::MemPool(PtrSize uCount) : m_uTotalCnt(uCount), m_uAvailableCnt(uCount)
	{
		m_pImpl = ETL_NEW("ETL::Memory::MemPool::m_pImpl") MemPoolImpl<CanHoldAPointer(sizeof(T))>(sizeof(T), uCount);
		m_uTotalCnt = uCount;
		m_uAvailableCnt = uCount;
	}

	template<typename T>
	MemPool<T>::~MemPool()
	{
		ETL_DELETE m_pImpl;
	}

	template<typename T>
	T& MemPool<T>::Request()
	{
		--m_uAvailableCnt;
		T& obj = *((T*)(m_pImpl->Request()));
		return  obj;
	}

	template<typename T>
	void MemPool<T>::Return(T& obj)
	{
		++m_uAvailableCnt;
		m_pImpl->Return((void*)&obj);
	}
}
}