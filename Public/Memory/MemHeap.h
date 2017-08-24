#pragma once

#include "Utility/Types.h"

namespace ETL
{
namespace Memory
{
	class MemHeap;

	template<typename T>
	struct MemHandle
	{
		T* operator->() const;
		T& operator*() const;
		T& operator[](unsigned int uIdx);

	private:
		MemHeap* m_pHeap;
		PtrSize* m_pAddr;

		friend class MemHeap;
	};

	class MemHeap
	{
	public:
		MemHeap(PtrSize uSize);
		~MemHeap();
		MemHeap(const MemHeap&) = delete;
		MemHeap& operator=(const MemHeap&) = delete;

		template<typename T>
		MemHandle<T> Request(PtrSize uCount = 1);

		template<typename T>
		void Return(const MemHandle<T>& handle);

		void Defragment(int64_t nMicroseconds = 0);

	private:
		void* m_pMemory;
		PtrSize m_uFreeStart;
		PtrSize m_uHandleStart;
		PtrSize m_uSize;
		PtrSize m_uAvailable;
		PtrSize* m_pUnusedHead;
		PtrSize m_uDefragOffset;
		PtrSize m_uLastUsedOffset;

		PtrSize* GetAvailableAddress();
		void WriteMemHeader(PtrSize* pHandleAddr, PtrSize uBlockSize);

		template<typename> friend struct MemHandle;
	};
}
}

#include "MemHeap.hpp"