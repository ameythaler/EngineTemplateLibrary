#pragma once

#include "Utility/Types.h"
#include "Utility/Macros.h"
#include <cstdio>
#include <cstdarg>

namespace ETL
{
namespace Filesystem
{
	class BaseFile
	{
		ETL_DISABLECOPYING(BaseFile);

	public:
		enum class AccessMode : uint8
		{
			ReadOnly,
			WriteAppend,
			WriteTruncate
		};

		enum class ContentMode : uint8
		{
			Text,
			Binary
		};

		BaseFile();
		BaseFile(const EtlString& filename, AccessMode accessMode, ContentMode contentMode);
		~BaseFile();

		bool Open(const EtlString& filename, AccessMode accessMode, ContentMode contentMode);
		void Close();
		void Flush();

		bool Seek(int32_t position);
		int32 GetPosition();

		void Write(const char* szFormat, ...);
		void Write(const wchar_t* szFormat, ...);
		void WriteData(const void* pData, size_t dataSize);

		void ReadLine(char* szText, int32 maxLen);
		void ReadLine(wchar_t* szText, int32 maxLen);
		size_t Read(void* pData, size_t dataSize);

		char ReadChar();
		wchar_t ReadCharW();

		inline bool IsOpen() const { return m_pFile != nullptr; }
		inline bool IsEndOfFile() const { return feof(m_pFile) != 0; }

	private:
		FILE* m_pFile;
	};
}
}