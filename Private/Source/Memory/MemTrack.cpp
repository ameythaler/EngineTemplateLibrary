#include "Memory/MemTrack.h"
#include "Memory/InternalAllocator.h"
#include <stdint.h>
#include <unordered_map>
#include "Hash.h"
#include "SimpleMutex.h"
#include <string.h>

using std::unordered_map;

#if ETL_MSVC
#pragma init_seg(".CRT$XCB")
#endif // ETL_MSVC

#if ETL_DEBUG

#if ETL_LLVM || ETL_GCC
void* operator new(size_t size)
{
	return QLib::MemTrack::Instance().Track(size, "Anonymous");
}

void* operator new[](size_t size)
{
	return QLib::MemTrack::Instance().Track(size, "AnonymousArray");
}

void operator delete(void* ptr) noexcept
{
	QLib::MemTrack::Instance().Release(ptr);
}

void operator delete[](void* ptr) noexcept
{
	QLib::MemTrack::Instance().Release(ptr);
}
#endif // ETL_LLVM || ETL_GCC

namespace ETL
{
namespace Memory
{
	MemTrack* MemTrack::sm_pDbgInstance = &MemTrack::Instance();

	const char* FindLastChar(const char* string, char ch)
	{
		int32_t len = (int32_t)strlen(string);
		for (int32_t i = len - 1; i >= 0; --i)
		{
			if (string[i] == ch)
				return &string[i];
		}
		return nullptr;
	}

	struct VarRecord
	{
		size_t Size;
		char* Tag;
		char* File;
		int Line;
		uint32_t Count;
		uint64_t Hash;
	};

	struct AllocRecord
	{
		size_t Size;
		VarRecord* Record;
	};

	typedef unordered_map<uint64_t, VarRecord, std::hash<uint64_t>, std::equal_to<uint64_t>, InternalAllocator<std::pair<const uint64_t, VarRecord>>> VarRecordMap;
	typedef unordered_map<void*, AllocRecord>::value_type AllocValType;
	typedef unordered_map<void*, AllocRecord, std::hash<void*>, std::equal_to<void*>, InternalAllocator<AllocValType>> AllocRecordMap;

	class Tracker
	{
	public:
		void Track(void* ptr, size_t size, const char* tag, const char* file, int line)
		{
			SimpleScopeLock lock(trackMutex);
#if ETL_WIN
			const char* filename = FindLastChar(file, '\\');
#elif ETL_MAC || ETL_LINUX
			const char* filename = FindLastChar(file, '/');
#endif
			if (filename == nullptr)
				filename = file;
			else
				filename = &filename[1]; // Remove the backslash

			uint64_t hash = QHash::FNV64(tag, strlen(tag));
			hash ^= QHash::FNV64(filename, strlen(filename));
			hash ^= line;

			auto varIter = m_TagMap.find(hash);
			if (varIter == m_TagMap.end())
			{
				VarRecord vr;
				vr.Size = size;
				vr.Tag = (char*)malloc((strlen(tag) + 1) * sizeof(char));
				strcpy(vr.Tag, tag);
				vr.File = (char*)malloc((strlen(filename) + 1) * sizeof(char));
				strcpy(vr.File, filename);
				vr.Line = line;
				vr.Hash = hash;
				vr.Count = 1;

				varIter = m_TagMap.emplace(std::make_pair(hash, vr)).first;
			}
			else
			{
				varIter->second.Size += size;
				varIter->second.Count++;
			}

			AllocRecord ar;
			ar.Size = size;
			ar.Record = &varIter->second;
			m_MemMap[ptr] = ar;
		}

		void Release(void* ptr)
		{
			SimpleScopeLock lock(trackMutex);
			auto allocIter = m_MemMap.find(ptr);
			if (allocIter != m_MemMap.end())
			{
				allocIter->second.Record->Count--;
				allocIter->second.Record->Size -= allocIter->second.Size;
				if (allocIter->second.Record->Count == 0)
				{
					free(allocIter->second.Record->Tag);
					free(allocIter->second.Record->File);
					m_TagMap.erase(allocIter->second.Record->Hash);
				}
				m_MemMap.erase(ptr);
			}
		}

		~Tracker()
		{
			FILE* file = fopen("memdump.txt", "w");

			char buff[256];
			sprintf(buff, "%-40s%-40s%-10s%-10s%-10s\n", "Tag", "File", "Line", "Size", "Count");
			fwrite(buff, strlen(buff) * sizeof(char), 1, file);
			for (auto iter : m_TagMap)
			{
				sprintf(buff, "%-40s%-40s%-10i%-10zu%-10i\n", iter.second.Tag, iter.second.File, iter.second.Line, iter.second.Size, iter.second.Count);
				fwrite(buff, strlen(buff) * sizeof(char), 1, file);
				free(iter.second.Tag);
				free(iter.second.File);
			}
			fclose(file);
		}

	private:
		VarRecordMap m_TagMap;
		AllocRecordMap m_MemMap;
		SimpleMutex trackMutex;
	};

	MemTrack::MemTrack()
	{
		m_pTracker = (void*)malloc(sizeof(Tracker));
		new(m_pTracker)Tracker();
	}

	MemTrack::~MemTrack()
	{
		Tracker* pTracker = (Tracker*)m_pTracker;
		pTracker->~Tracker(); // We have to manually destruct because we use malloc() and free()
		free(m_pTracker);
		sm_pDbgInstance = nullptr;
	}

	void* MemTrack::Track(size_t size, const char* tag, const char* file, int line)
	{
		Tracker* pTracker = (Tracker*)m_pTracker;
		void* ptr = malloc(size);
		pTracker->Track(ptr, size, tag, file, line);
		return ptr;
	}

	void* MemTrack::Track(size_t size, const char* tag)
	{
		Tracker* pTracker = (Tracker*)m_pTracker;
		void* ptr = malloc(size);
		pTracker->Track(ptr, size, tag, "None", 0);
		return ptr;
	}

	void MemTrack::Release(void* ptr)
	{
		Tracker* pTracker = (Tracker*)m_pTracker;
		pTracker->Release(ptr);
		free(ptr);
	}
}
}

#endif // ETL_DEBUG