#include "catch.hpp"
#include "Utility/Types.h"

#define _ETL_TEST_STRING "A test string."

using namespace ETL;

SCENARIO("wide and multi-byte strings can be converted back and forth", "[string]")
{
	GIVEN("A wide string with some text")
	{
		WideString wideStr = ETL_TEXT(_ETL_TEST_STRING);

		WHEN("the wide string is converted to a multi-byte string")
		{
			MbString mbStr;
			WideStringToMbString(mbStr, wideStr);

			THEN("the multi-byte string matches the wide string")
			{
				REQUIRE(strcmp(mbStr.c_str(), _ETL_TEST_STRING) == 0);
			}
		}
	}

	GIVEN("A multi-byte string with some text")
	{
		MbString mbString = _ETL_TEST_STRING;

		WHEN("the multi-byte string is converted to a wide string")
		{
			WideString wideStr;
			MbStringToWideString(wideStr, mbString);

			THEN("the wide string matches the multi-byte string")
			{
				REQUIRE(wcscmp(wideStr.c_str(), ETL_TEXT(_ETL_TEST_STRING)) == 0);
			}
		}
	}
}