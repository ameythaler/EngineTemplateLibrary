#pragma once

#include "Utility/Platform.h"
#include "STLExtensions/extended_string.h"
#include "Memory/MemTrack.h"
#include <inttypes.h>
#include <wchar.h>
#include <sstream>
#include <vector>

namespace ETL
{
#if ETL_32BIT
	typedef uint32_t PtrSize;
#elif ETL_64BIT
	typedef uint64_t PtrSize;
#endif // ETL_32BIT

	typedef STLExtensions::extended_string<char> MbString;
	typedef STLExtensions::extended_string<wchar_t> WideString;
	typedef std::basic_string<char16_t> Wide16String;
	typedef std::basic_stringstream<char> MbStringStream;
	typedef std::basic_stringstream<wchar_t> WideStringStream;

#if ETL_UNICODE
	typedef WideString EtlString;
	typedef WideStringStream EtlStringStream;
	typedef wchar_t EtlChar;
#define ETL_TEXT(x) L##x
#else
	typedef MbString EtlString;
	typedef MbString EtlStringStream;
	typedef char EtlChar;
#define ETL_TEXT(x) x
#endif // ETL_UNICODE

	Wide16String ToWide16StringFromWideString(const WideString& string);
	WideString FromWide16StringToWideString(const Wide16String& string);
	Wide16String ToWide16StringFromMbString(const MbString& string);
	MbString FromWide16StringToMbString(const Wide16String& string);

	inline Wide16String ToWide16String(const EtlString& string)
	{
#if ETL_UNICODE
		return ToWide16StringFromWideString(string);
#else // ETL_UNICODE
		return ToWide16StringFromMbString(string);
#endif // ETL_UNICODE
	}
	inline EtlString FromWide16String(const Wide16String& string)
	{
#if ETL_UNICODE
#else // ETL_UNICDOE
#endif // ETL_UNICDOE
	}

	typedef uint8_t byte;
	typedef uint16_t word;
	typedef uint32_t dword;
	typedef uint64_t qword;

	typedef uint8_t uint8;
	typedef uint16_t uint16;
	typedef uint32_t uint32;
	typedef uint64_t uint64;

	typedef int8_t int8;
	typedef int16_t int16;
	typedef int32_t int32;
	typedef int64_t int64;

	struct LocalCharPtr
	{
		char* Ptr;

		LocalCharPtr() : Ptr(nullptr) { }
		LocalCharPtr(unsigned int size) { Ptr = ETL_NEW("ETL:Core:LocalCharPtr:Ptr") char[size]; }
		LocalCharPtr(const EtlString& str);
		~LocalCharPtr() { ETL_DELETE[] Ptr; }
		operator char*() { return Ptr; }
		char** operator&() { return &Ptr; }
		char operator*() { return *Ptr; }
		char operator[](unsigned int index) { return Ptr[index]; }
		operator EtlString() const;
	};

	void WideStringToMbCharArray(char** mbCharArray, const WideString& str);
	void WideStringToMbString(MbString& out, const WideString& str);
	void MbCharArrayToWideString(WideString& str, const char* mbCharArray);
	void MbStringToWideString(WideString& out, const MbString& str);

#if ETL_UNICODE
	inline void EtlStringToMbCharArray(char** mbCharArray, const EtlString& str)
	{
		WideStringToMbCharArray(mbCharArray, str);
	}

	inline void MbCharArrayToEtlString(EtlString& str, const char* mbCharArray)
	{
		MbCharArrayToWideString(str, mbCharArray);
	}

	inline EtlString WideStringToEtlString(const WideString& str)
	{
		return str;
	}

	inline WideString EtlStringToWideString(const EtlString& str)
	{
		return str;
	}

	inline EtlString MbStringToEtlString(const MbString& str)
	{
		EtlString out;
		MbStringToWideString(out, str);
		return out;
	}

	inline MbString EtlStringToMbString(const EtlString& str)
	{
		MbString out;
		WideStringToMbString(out, str);
		return out;
	}
#else // ETL_UNICODE
	inline void EtlStringToMbCharArray(char** mbCharArray, const EtlString& str)
	{
		*mbCharArray = str.c_str();
	}

	inline void MbCharArrayToEtlString(EtlString& str, const char* mbCharArray)
	{
		str = mbCharArray;
	}

	inline EtlString WideStringToEtlString(const WideString& str)
	{
		EtlString out;
		WideStringToMbString(out, str);
		return out;
	}

	inline WideString EtlStringToWideString(const EtlString& str)
	{
		MbString out;
		MbStringToWideString(out, str);
		return out;
	}

	inline EtlString MbStringToEtlString(const MbString& str)
	{
		return str;
	}

	inline MbString EtlStringToMbString(const EtlString& str)
	{
		return str;
	}
#endif // ETL_UNICODE
}