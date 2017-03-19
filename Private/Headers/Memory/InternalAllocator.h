#pragma once

#include <memory>

namespace ETL
{
namespace Memory
{
	template<typename T>
	class InternalAllocator : public std::allocator < T >
	{
	public:
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T value_type;

		template<typename U>
		struct rebind
		{
			typedef InternalAllocator<U> other;
		};

		InternalAllocator() { }

		template<typename U>
		InternalAllocator(const InternalAllocator<U>&) { }

		pointer allocate(size_type n, const void* hint = 0)
		{
			return (pointer)malloc(n * sizeof(T));
		}

		void deallocate(pointer p, size_type n)
		{
			return free((void*)p);
		}
	};
}
}