#pragma once

#include "Utility/Platform.h"
#include "Utility/Types.h"

namespace ETL
{
namespace Memory
{
	typedef PtrSize MemStackMark;

	class MemStack
	{
	public:
		MemStack(PtrSize uStackSize = 2000u);
		~MemStack();
		MemStack(const MemStack&) = delete;
		MemStack& operator=(const MemStack&) = delete;

		inline MemStackMark Mark() { return m_uTop; }
		template<typename T> T* Push(PtrSize uCount = 1);
		inline void Pop(MemStackMark mark) { m_uTop = mark; }

		inline PtrSize GetStackSize() const { return m_uStackSize; }

	private:
		void* m_pStack;
		PtrSize m_uTop;
		PtrSize m_uStackSize;
	};
}
}

#include "MemStack.hpp"