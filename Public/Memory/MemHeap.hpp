namespace ETL
{
namespace Memory
{
	template<typename T>
	T* MemHandle<T>::operator->() const
	{
		byte* pMemory = (byte*)m_pHeap->m_pMemory;
		return (T*)(&pMemory[*m_pAddr + 2 * sizeof(PtrSize)]);
	}

	template<typename T>
	T& MemHandle<T>::operator*() const
	{
		byte* pMemory = (byte*)m_pHeap->m_pMemory;
		return (T&)(pMemory[*m_pAddr + 2 * sizeof(PtrSize)]);
	}

	template<typename T>
	T& MemHandle<T>::operator[](unsigned int uIdx)
	{
		byte* pMemory = (byte*)m_pHeap->m_pMemory;
		T* pData = (T*)(&pMemory[*m_pAddr + 2 * sizeof(PtrSize)]);
		return pData[uIdx];
	}

	template<typename T>
	MemHandle<T> MemHeap::Request(PtrSize uCount)
	{
		PtrSize uObjSize = (sizeof(T) * uCount) + sizeof(PtrSize) * 2;
		MemHandle<T> handle;
		PtrSize uNeededSize = uObjSize + ((m_pUnusedHead) ? 0 : sizeof(PtrSize));
		if (m_uAvailable >= uNeededSize || uCount == 0)
		{
			handle.m_pHeap = this;
			handle.m_pAddr = GetAvailableAddress();

			if (m_uHandleStart - m_uFreeStart < uObjSize) // We need to defragment first.
				Defragment();

			*handle.m_pAddr = m_uFreeStart;
			WriteMemHeader(handle.m_pAddr, uObjSize);
			m_uFreeStart += uObjSize;
			m_uAvailable -= uNeededSize;
		}
		else
		{
			handle.m_pHeap = nullptr;
		}

		return handle;
	}

	template<typename T>
	void MemHeap::Return(const MemHandle<T>& handle)
	{
		if (handle.m_pHeap == this)
		{
			PtrSize* pAddr = handle.m_pAddr;

			byte* pMemory = (byte*)m_pMemory;
			PtrSize uBlockSize = (PtrSize)(pMemory[*pAddr]);
			memset(&pMemory[*pAddr], 0, uBlockSize);

			*pAddr = (PtrSize)m_pUnusedHead;
			m_pUnusedHead = pAddr;
			m_uAvailable += uBlockSize;
		}
	}
}
}