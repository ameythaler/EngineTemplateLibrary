#include "Memory/MemStack.h"
#include "Memory/MemTrack.h"

namespace ETL
{
namespace Memory
{
	MemStack::MemStack(PtrSize uStackSize)
	{
		m_pStack = ETL_ALLOC("ETL::Memory::MemStack::m_pStack", uStackSize);
		m_uTop = 0;
		m_uStackSize = uStackSize;
	}

	MemStack::~MemStack()
	{
		ETL_FREE(m_pStack);
		m_pStack = nullptr;
		m_uTop = 0;
		m_uStackSize = 0;
	}
}
}