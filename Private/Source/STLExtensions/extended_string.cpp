#include "STLExtensions/extended_string.h"
#include <locale.h>

namespace ETL
{
namespace STLExtensions
{
	// new_line()
#if ETL_WIN

	template<>
	const char* new_line()
	{
		return "\n\r";
	}

	template<>
	const wchar_t* new_line()
	{
		return L"\n\r";
	}

	template<>
	const char16_t* new_line()
	{
		return (char16_t*)L"\n\r";
	}

	template<>
	const char32_t* new_line()
	{
		return (char32_t*)L"\n\r";
	}

#else

	template<>
	const char* new_line()
	{
		return "\n\r";
	}

	template<>
	const wchar_t* new_line()
	{
		return L"\n\r";
	}

	template<>
	const char16_t* new_line()
	{
		return u"\n\r";
	}

	template<>
	const char32_t* new_line()
	{
		return U"\n\r";
	}

#endif // Q_WIN

	// extended_string_to_upper
	template<>
	extended_string<char>& extended_string_to_upper(extended_string<char>& str)
	{
		const std::locale& loc = std::locale();
		for (extended_string<char>::iterator charIter = str.begin(); charIter != str.end(); charIter++)
			*charIter = std::use_facet<std::ctype<char>>(loc).toupper(*charIter);
		return str;
	}

	template<>
	extended_string<wchar_t>& extended_string_to_upper(extended_string<wchar_t>& str)
	{
		const std::locale& loc = std::locale();
		for (extended_string<wchar_t>::iterator charIter = str.begin(); charIter != str.end(); charIter++)
			*charIter = std::use_facet<std::ctype<wchar_t>>(loc).toupper(*charIter);
		return str;
	}

	// extended_string_as_upper
	template<>
	extended_string<char> extended_string_as_upper(const extended_string<char>& str)
	{
		extended_string<char> outString = str;
		const std::locale& loc = std::locale();
		for (extended_string<char>::iterator charIter = outString.begin(); charIter != outString.end(); charIter++)
			*charIter = std::use_facet<std::ctype<char>>(loc).toupper(*charIter);
		return outString;
	}

	template<>
	extended_string<wchar_t> extended_string_as_upper(const extended_string<wchar_t>& str)
	{
		extended_string<wchar_t> outString = str;
		const std::locale& loc = std::locale();
		for (extended_string<wchar_t>::iterator charIter = outString.begin(); charIter != outString.end(); charIter++)
			*charIter = std::use_facet<std::ctype<wchar_t>>(loc).toupper(*charIter);
		return outString;
	}

	// extended_string_to_lower
	template<>
	extended_string<char>& extended_string_to_lower(extended_string<char>& str)
	{
		const std::locale& loc = std::locale();
		for (extended_string<char>::iterator charIter = str.begin(); charIter != str.end(); charIter++)
			*charIter = std::use_facet<std::ctype<char>>(loc).tolower(*charIter);
		return str;
	}

	template<>
	extended_string<wchar_t>& extended_string_to_lower(extended_string<wchar_t>& str)
	{
		const std::locale& loc = std::locale();
		for (extended_string<wchar_t>::iterator charIter = str.begin(); charIter != str.end(); charIter++)
			*charIter = std::use_facet<std::ctype<wchar_t>>(loc).tolower(*charIter);
		return str;
	}

	// extended_string_as_lower
	template<>
	extended_string<char> extended_string_as_lower(const extended_string<char>& str)
	{
		extended_string<char> outString = str;
		const std::locale& loc = std::locale();
		for (extended_string<char>::iterator charIter = outString.begin(); charIter != outString.end(); charIter++)
			*charIter = std::use_facet<std::ctype<char>>(loc).tolower(*charIter);
		return outString;
	}

	template<>
	extended_string<wchar_t> extended_string_as_lower(const extended_string<wchar_t>& str)
	{
		extended_string<wchar_t> outString = str;
		const std::locale& loc = std::locale();
		for (extended_string<wchar_t>::iterator charIter = outString.begin(); charIter != outString.end(); charIter++)
			*charIter = std::use_facet<std::ctype<wchar_t>>(loc).tolower(*charIter);
		return outString;
	}
}
}