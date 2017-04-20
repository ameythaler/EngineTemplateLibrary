#include <string.h>
#include "Memory/MemHeap.h"
#include "Memory/MemTrack.h"
#include "Utility/Timer.h"

using ETL::Utility::Timer;

namespace
{
	const ETL::PtrSize cBytesToCheck = 100; // Bytes to check per iteration.
}

namespace ETL
{
namespace Memory
{
	MemHeap::MemHeap(PtrSize uSize) : m_uSize(uSize), m_uHandleStart(uSize), m_uFreeStart(0),
		m_uAvailable(m_uSize), m_pUnusedHead(nullptr), m_uDefragOffset(0), m_uLastUsedOffset(0)
	{
		m_pMemory = ETL_ALLOC("ETL::Memory::MemHeap::m_pMemory", uSize);
		memset(m_pMemory, 0, uSize);
	}

	MemHeap::~MemHeap()
	{
		ETL_FREE(m_pMemory);
	}

	PtrSize* MemHeap::GetAvailableAddress()
	{
		PtrSize* pAddr;
		if (m_pUnusedHead)
		{
			pAddr = m_pUnusedHead;
			m_pUnusedHead = (PtrSize*)*m_pUnusedHead;
		}
		else
		{
			m_uHandleStart -= sizeof(PtrSize);
			pAddr = (PtrSize*)&((byte*)m_pMemory)[m_uHandleStart];
		}
		return pAddr;
	}

	void MemHeap::WriteMemHeader(PtrSize* pHandleAddr, PtrSize uBlockSize)
	{
		PtrSize* pMemory = (PtrSize*)&((byte*)m_pMemory)[*pHandleAddr];
		pMemory[0] = uBlockSize;
		pMemory[1] = (PtrSize)pHandleAddr;
	}

	void MemHeap::Defragment(int64_t nMicroseconds)
	{
		int64_t nStartTime = Timer::Instance().GetMicroseconds();
		bool bOutOfTime = false;
		byte* pMemory = (byte*)m_pMemory;

		while (m_uDefragOffset < m_uFreeStart && m_uHandleStart - m_uFreeStart < m_uAvailable && !bOutOfTime)
		{
			for (PtrSize uTestOffset = 0; uTestOffset < cBytesToCheck && m_uDefragOffset < m_uFreeStart; ++uTestOffset)
			{
				if (pMemory[m_uDefragOffset]) // Skip nulled out bytes.
				{
					PtrSize* pBlockHeader = (PtrSize*)&pMemory[m_uDefragOffset];
					if (m_uDefragOffset - m_uLastUsedOffset > 0) // Space to move.
					{
						PtrSize uBlockSize = pBlockHeader[0];
						PtrSize* pAddr = (PtrSize*)(pBlockHeader[1]);
						memmove(&pMemory[m_uLastUsedOffset], &pMemory[m_uDefragOffset], pBlockHeader[0]);
						*pAddr = m_uLastUsedOffset;
						m_uLastUsedOffset += uBlockSize;
						PtrSize uUsedMem = (m_uLastUsedOffset <= m_uDefragOffset) ? 0 : m_uLastUsedOffset - m_uDefragOffset;
						memset(&pMemory[m_uDefragOffset + uUsedMem], 0, uBlockSize - uUsedMem);
						m_uDefragOffset += uBlockSize;
						uTestOffset += uBlockSize;
						m_uAvailable += uBlockSize - uUsedMem;
					}
					else // No space to move memory down.
					{
						m_uLastUsedOffset = m_uDefragOffset + pBlockHeader[0];
						m_uDefragOffset += pBlockHeader[0];
						uTestOffset += pBlockHeader[0];
					}
				}
				else
				{
					m_uDefragOffset++;
				}
			}

			if (nMicroseconds > 0)
				bOutOfTime = (Timer::Instance().GetMicroseconds() - nStartTime) >= nMicroseconds;
		}

		if (m_uDefragOffset >= m_uFreeStart) // We finished one defrag pass.
		{
			m_uFreeStart = m_uLastUsedOffset;
			m_uDefragOffset = 0;
			m_uLastUsedOffset = 0;
		}
	}
}
}