#pragma once

namespace ETL
{
	namespace Utility
	{
		template<typename A>
		struct CompareToVoidPointer
		{
			enum { result = sizeof(A) >= sizeof(void*) };
		};

		constexpr bool CanHoldAPointer(size_t typeSize)
		{
			return typeSize >= sizeof(void*);
		}
	}
}