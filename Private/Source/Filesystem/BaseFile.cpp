#include "Filesystem/BaseFile.h"

namespace ETL
{
namespace Filesystem
{
	BaseFile::BaseFile()
		: m_pFile(nullptr)
	{

	}

	BaseFile::BaseFile(const EtlString& filename, AccessMode accessMode, ContentMode contentMode)
	{
		Open(filename, accessMode, contentMode);
	}

	BaseFile::~BaseFile()
	{
		Close();
	}

	bool BaseFile::Open(const EtlString& filename, AccessMode accessMode, ContentMode contentMode)
	{
		bool bBinary = (contentMode == ContentMode::Binary);
#if ETL_WIN && ETL_UNICODE
		wchar_t* modeStr;
		switch (accessMode)
		{
		case AccessMode::ReadOnly:
			modeStr = (bBinary) ? L"rb" : L"r";
			break;
		case AccessMode::WriteAppend:
			modeStr = (bBinary) ? L"ab" : L"a";
			break;
		case AccessMode::WriteTruncate:
			modeStr = (bBinary) ? L"wb" : L"w";
			break;
		}
		if (_wfopen_s(&m_pFile, filename.c_str(), modeStr) != 0)
			return false;
#else // ETL_WIN
		char* modeStr;
		switch (accessMode)
		{
		case AccessMode::ReadOnly:
			modeStr = (bBinary) ? "rb" : "r";
			break;
		case AccessMode::WriteAppend:
			modeStr = (bBinary) ? "ab" : "a";
			break;
		case AccessMode::WriteTruncate:
			modeStr = (bBinary) ? "wb" : "w";
			break;
		}
		LocalCharPtr fileStr;
		EtlStringToMbCharArray(&fileStr, filename);
		m_pFile = fopen(fileStr, modeStr);
#endif // ETL_WIN

		if (m_pFile && !bBinary) // We always write text in wide char mode.
			fwide(m_pFile, 1);

		return m_pFile != nullptr;
	}

	void BaseFile::Close()
	{
		if (m_pFile)
		{
			fclose(m_pFile);
			m_pFile = nullptr;
		}
	}

	void BaseFile::Flush()
	{
		fflush(m_pFile);
	}

	bool BaseFile::Seek(int32 position)
	{
		return fseek(m_pFile, position, SEEK_SET) == 0;
	}

	int32 BaseFile::GetPosition()
	{
		return ftell(m_pFile);
	}

	void BaseFile::Write(const char* szFormat, ...)
	{
		va_list args;
		va_start(args, szFormat);
		vfprintf(m_pFile, szFormat, args);
		va_end(args);
	}

	void BaseFile::Write(const wchar_t* szFormat, ...)
	{
		va_list args;
		va_start(args, szFormat);
		vfwprintf(m_pFile, szFormat, args);
		va_end(args);
	}

	void BaseFile::WriteData(const void* pData, size_t dataSize)
	{
		fwrite(pData, sizeof(uint8), dataSize, m_pFile);
	}

	void BaseFile::ReadLine(char* szText, int32 maxLen)
	{
		fgets(szText, maxLen, m_pFile);
	}

	void BaseFile::ReadLine(wchar_t* szText, int32 maxLen)
	{
		fgetws(szText, maxLen, m_pFile);
	}

	size_t BaseFile::Read(void* pData, size_t dataSize)
	{
		return fread(pData, sizeof(uint8), dataSize, m_pFile);
	}

	char BaseFile::ReadChar()
	{
		return fgetc(m_pFile);
	}

	wchar_t BaseFile::ReadCharW()
	{
		return fgetwc(m_pFile);
	}
}
}