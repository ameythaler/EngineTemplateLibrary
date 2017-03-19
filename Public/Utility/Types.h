#ifndef TYPES_H_
#define TYPES_H_

#include "Utility/Platform.h"
#include "STLExtensions/extended_string.h"
#include "Memory/MemTrack.h"
#include <inttypes.h>
#include <wchar.h>
#include <sstream>
#include <vector>

namespace ETL
{
namespace Core
{
#if ETL_32BIT // TODO: Need a 64 and 32 bit flag because this isn't Mac specific.
	typedef uint32_t PtrSize;
#elif ETL_64BIT
	typedef uint64_t PtrSize;
#endif // ETL_32BIT

	typedef STLExtensions::extended_string<char> MbString;
	typedef STLExtensions::extended_string<wchar_t> WideString;
	typedef STLExtensions::extended_string<char16_t> Wide16String;
	typedef std::basic_stringstream<char> MbStringStream;
	typedef std::basic_stringstream<wchar_t> WideStringStream;

#if ETL_UNICODE
	typedef WideString EtlString;
	typedef WideStringStream EtlStringStream;
	typedef wchar_t EtlChar;
#define ETL_TEXT(x) L"x"
#else
	typedef MbString EtlString;
	typedef MbString EtlStringStream;
	typedef char EtlChar;
#define ETL_TEXT(x) "x"
#endif // ETL_UNICODE

	Wide16String ToWide16String(const EtlString& string);
	EtlString ToNetString(const Wide16String& string);

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
		~LocalCharPtr() { ETL_DELETE[] Ptr; }
		operator char*() { return Ptr; }
		char** operator&() { return &Ptr; }
		char operator*() { return *Ptr; }
		char operator[](unsigned int index) { return Ptr[index]; }
	};

	void QStringToLower(qString& string);
	void QStringAsLower(qString& outString, const qString& inString);
	qString QStringAsLower(const qString& string);
	void QStringToUpper(qString& string);
	void QStringAsUpper(qString& outString, const qString& inString);
	qString QStringAsUpper(const qString& string);
	void QStringToMBCharArray(char** mbCharArray, const qString& str);
	void MBCharArrayToQString(qString& str, const char* mbCharArray);
}
}

#endif
