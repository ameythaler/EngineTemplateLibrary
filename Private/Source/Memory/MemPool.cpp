#include "Memory/MemPool.h"
#include "Memory/MemTrack.h"

namespace ETL
{
namespace Memory
{
	MemPoolImpl<1>::MemPoolImpl(PtrSize uObjectSize, PtrSize uCount)
	{
		m_pMemory = ETL_ALLOC("ETL::Memory::MemPoolImpl<1>::m_pMemory", uObjectSize * uCount);
		char* pArray = (char*)m_pMemory;
		void* pPtr = &pArray[(uCount - 1) * uObjectSize];
		*(void**)pPtr = nullptr;
		void* pLastPtr = pPtr;
		if (uCount > 1)
		{
			for (PtrSize uCnt = 2; uCnt <= uCount; ++uCnt)
			{
				PtrSize uIdx = uCount - uCnt;
				pPtr = &pArray[uIdx * uObjectSize];
				*(void**)pPtr = pLastPtr;
				pLastPtr = pPtr;
			}
		}

		m_pHead = m_pMemory;
	}

	MemPoolImpl<1>::~MemPoolImpl()
	{
		ETL_FREE(m_pMemory);
	}

	void* MemPoolImpl<1>::Request()
	{
		void* pObj = m_pHead;
		m_pHead = *((void**)m_pHead);
		return pObj;
	}

	void MemPoolImpl<1>::Return(void* pObj)
	{
		*((void**)pObj) = m_pHead;
		m_pHead = pObj;
	}

	MemPoolImpl<0>::MemPoolImpl(PtrSize uObjectSize, PtrSize uCount) : m_pUsedHead(nullptr)
	{
		PtrSize dataSize = uObjectSize * uCount;
		m_pMemory = ETL_ALLOC("ETL::Memory::MemPoolImpl<0>::m_pMemory", dataSize);
		char* pBytes = (char*)m_pMemory;
		m_pPoolNodeMemory = ETL_NEW("ETL::Memory::MemPoolImpl<0>::m_pPoolNodeMemory") PoolNode[uCount];
		m_pPoolNodeMemory[uCount - 1].pNext = nullptr;
		m_pPoolNodeMemory[uCount - 1].pData = (void*)(&pBytes[dataSize - uObjectSize]);
		PoolNode* pLastNode = &m_pPoolNodeMemory[uCount - 1];
		for (PtrSize uCnt = 2; uCnt <= uCount; ++uCnt)
		{
			PtrSize uIdx = uCount - uCnt;
			m_pPoolNodeMemory[uIdx].pNext = pLastNode;
			m_pPoolNodeMemory[uIdx].pData = (void*)(&pBytes[dataSize - uCnt * uObjectSize]);
			pLastNode = &m_pPoolNodeMemory[uIdx];
		}
		m_pFreeHead = pLastNode;
	}

	MemPoolImpl<0>::~MemPoolImpl()
	{
		ETL_FREE(m_pMemory);
		ETL_DELETE[] m_pPoolNodeMemory;
	}

	void* MemPoolImpl<0>::Request()
	{
		void* pObj = m_pFreeHead->pData;
		PoolNode* pNextNode = m_pFreeHead->pNext;
		m_pFreeHead->pNext = m_pUsedHead;
		m_pUsedHead = m_pFreeHead;
		m_pFreeHead = pNextNode;
		return pObj;
	}

	void MemPoolImpl<0>::Return(void* pObj)
	{
		PoolNode* pNode = m_pUsedHead;
		m_pUsedHead = m_pUsedHead->pNext;
		pNode->pData = pObj;
		pNode->pNext = m_pFreeHead;
		m_pFreeHead = pNode;
	}
}
}