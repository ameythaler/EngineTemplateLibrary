#include "Utility/Types.h"
#include "Memory/MemTrack.h"

namespace ETL
{
namespace Utility
{
	LocalCharPtr::LocalCharPtr(const EtlString& str)
	{
		EtlStringToMbCharArray(&Ptr, str);
	}

	LocalCharPtr::operator EtlString() const
	{
		EtlString str;
		MbCharArrayToEtlString(str, Ptr);
		return str;
	}

	Wide16String ToWide16StringFromWideString(const WideString& string)
	{
		Wide16String retVal;
		for (wchar_t ch : string)
		{
			retVal.push_back((char16_t)ch);
		}
		return retVal;
	}

	WideString FromWide16StringToWideString(const Wide16String& string)
	{
		WideString retVal;
		for (char16_t ch : string)
			retVal.push_back((wchar_t)ch);
		return retVal;
	}

	Wide16String ToWide16StringFromMbString(const MbString& string)
	{
		WideString wideStr;
		MbStringToWideString(wideStr, string);
		return ToWide16StringFromWideString(wideStr);
	}

	MbString FromWide16StringToMbString(const Wide16String& string)
	{
		MbString retVal;
		WideString wideStr = FromWide16StringToWideString(string);
		WideStringToMbString(retVal, wideStr);
		return retVal;
	}

	void WideStringToMbCharArray(char** mbCharArray, const WideString& str)
	{
		*mbCharArray = ETL_NEW("ETL::Utility::WideStringToMbCharArray::mbCharArray") char[str.length() + 1];
		wcstombs(*mbCharArray, &str[0], str.length() + 1);
	}

	void WideStringToMbString(MbString& out, const WideString& str)
	{
		out.resize(str.length());
		wcstombs(&out[0], &str[0], str.length());
	}

	void MbCharArrayToWideString(WideString& str, const char* mbCharArray)
	{
		size_t strLen = strlen(mbCharArray);
		str.resize(strLen);
		mbstowcs(&str[0], mbCharArray, strLen);
	}

	void MbStringToWideString(WideString& out, const MbString& str)
	{
		out.resize(str.length());
		mbstowcs(&out[0], &str[0], str.length());
	}
}
}