#include "catch.hpp"
#include "Math/Math.h"
#include "Math/Matrix4x4.h"

using namespace ETL::Math;
using namespace ETL;

//////////////////////////////////////////////////////////////////////////
// Matrix4x4f
//////////////////////////////////////////////////////////////////////////
SCENARIO("matrix4x4 float math produces correct results", "[matrix4x4f]")
{
	GIVEN("three Matrix4x4f objects")
	{
		Matrix4x4f a;
		Matrix4x4f b(Vector4f(1.0f, 2.0f, 3.0f, 4.0f), Vector4f(5.0f, 6.0f, 7.0f, 8.0f), Vector4f(9.0f, 10.0f, 11.0f, 12.0f), Vector4f(13.0f, 14.0f, 15.0f, 16.0f));
		Matrix4x4f c(b);

		REQUIRE(a == Matrix4x4f::Identity);
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("matrix addition is performed")
		{
			c = b + a;
			a += b;
			b += Matrix4x4f::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE(a == c);
				REQUIRE((b.M00 == 2.0f && b.M01 == 3.0f && b.M02 == 4.0f && b.M03 == 5.0f
					&& b.M10 == 6.0f && b.M11 == 7.0f && b.M12 == 8.0f && b.M13 == 9.0f
					&& b.M20 == 10.0f && b.M21 == 11.0f && b.M22 == 12.0f && b.M23 == 13.0f
					&& b.M30 == 14.0f && b.M31 == 15.0f && b.M32 == 16.0f && b.M33 == 17.0f));
			}
		}

		WHEN("matrix subtraction is performed")
		{
			c -= a;
			a = b - a;
			b -= Matrix4x4f::One;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE(a == c);
				REQUIRE((b.M00 == 0.0f && b.M01 == 1.0f && b.M02 == 2.0f && b.M03 == 3.0f
					&& b.M10 == 4.0f && b.M11 == 5.0f && b.M12 == 6.0f && b.M13 == 7.0f
					&& b.M20 == 8.0f && b.M21 == 9.0f && b.M22 == 10.0f && b.M23 == 11.0f
					&& b.M30 == 12.0f && b.M31 == 13.0f && b.M32 == 14.0f && b.M33 == 15.0f));
			}
		}
	}
}