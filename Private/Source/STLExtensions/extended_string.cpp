#include "STLExtensions/extended_string.h"

namespace ETL
{
namespace STLExtensions
{
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
}
}