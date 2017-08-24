#pragma once

#include "Utility/Types.h"
#include "Utility/TemplateMetaProgramming.h"

namespace ETL
{
namespace Memory
{
	template<int GreaterThanVoid>
	struct MemPoolImpl;

	template<typename T>
	class MemPool
	{
	public:
		MemPool(PtrSize uCount);
		~MemPool();
		MemPool(const MemPool&) = delete;
		MemPool& operator=(const MemPool&) = delete;

		T& Request();
		void Return(T& obj);

		inline PtrSize GetReservedCount() const { return m_uTotalCnt; }
		inline PtrSize GetAvailableCount() const { return m_uAvailableCnt; }

	private:
		MemPoolImpl<Utility::CanHoldAPointer(sizeof(T))> m_pImpl;
		//MemPoolImpl<CompareToVoidPointer<T>::result>* m_pImpl;
		PtrSize m_uTotalCnt;
		PtrSize m_uAvailableCnt;
	};

	template<>
	struct MemPoolImpl<1> // Larger than or equal to a pointer
	{
		void* m_pMemory;
		void* m_pHead;

		MemPoolImpl(PtrSize uObjectSize, PtrSize uCount);
		~MemPoolImpl();
		void* Request();
		void Return(void* pObj);
	};

	template<>
	struct MemPoolImpl <0> // Smaller than a pointer
	{
		struct PoolNode
		{
			PoolNode* pNext;
			void* pData;
		};

		void* m_pMemory;
		PoolNode* m_pPoolNodeMemory;
		PoolNode* m_pFreeHead;
		PoolNode* m_pUsedHead;

		MemPoolImpl(PtrSize uObjectSize, PtrSize uCount);
		~MemPoolImpl();
		void* Request();
		void Return(void* pObj);
	};
}
}

#include "MemPool.hpp"