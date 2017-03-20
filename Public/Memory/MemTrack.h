#pragma once

#include "Utility/Platform.h"
#include <stdlib.h>

#if ETL_DEBUG

namespace ETL
{
namespace Memory
{
	class MemTrack
	{
	public:
		static MemTrack& Instance()
		{
			static MemTrack instance;
			return instance;
		}

		void* Track(size_t size, const char* tag, const char* file, int line);
		void* Track(size_t size, const char* tag);
		void Release(void* ptr);

	private:
		MemTrack();
		~MemTrack();
	private:
		MemTrack(const MemTrack&) = delete;
		MemTrack& operator=(const MemTrack&) = delete;

		static MemTrack* sm_pDbgInstance;

		void* m_pTracker;
	};
}
}

inline void* operator new(size_t size, const char* tag, const char* file, int line) { return ETL::Memory::MemTrack::Instance().Track(size, tag, file, line); }
inline void* operator new[](size_t size, const char* tag, const char* file, int line) { return ETL::Memory::MemTrack::Instance().Track(size, tag, file, line); }
inline void operator delete(void* ptr, const char* tag, const char* file, int line) { ETL::Memory::MemTrack::Instance().Release(ptr); }
inline void operator delete[](void* ptr, const char* tag, const char* file, int line) { ETL::Memory::MemTrack::Instance().Release(ptr); }
inline void* EtlAlloc(const char* tag, size_t size, const char* file, int line) { return ETL::Memory::MemTrack::Instance().Track(size, tag, file, line); }
inline void EtlFree(void* ptr) { ETL::Memory::MemTrack::Instance().Release(ptr); }

#if ETL_MSVC && _MSC_VER < 1900

inline void* operator new(size_t size) { return ETL::Memory::MemTrack::Instance().Track(size, "Anonymous"); }
inline void* operator new[](size_t size) { return ETL::Memory::MemTrack::Instance().Track(size, "Anonymous"); }
inline void operator delete(void* ptr) { ETL::Memory::MemTrack::Instance().Release(ptr); }
inline void operator delete[](void* ptr) { ETL::Memory::MemTrack::Instance().Release(ptr); }

#endif


#define ETL_NEW(tag) new(tag, __FILE__, __LINE__)
#define ETL_DELETE delete
#define ETL_ALLOC(tag, size) EtlAlloc(tag, size, __FILE__, __LINE__)
#define ETL_FREE(ptr) EtlFree(ptr)

#else

#define ETL_NEW(tag) new
#define ETL_DELETE delete
#define ETL_ALLOC(tag, size) malloc(size)
#define ETL_FREE(ptr) free(ptr)

#endif
