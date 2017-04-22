#include "catch.hpp"
#include "Math/Math.h"
#include "Math/Vector2.h"

using namespace ETL::Math;
using namespace ETL;

SCENARIO("basic math functions and constants produce correct values", "[scalar]")
{
	GIVEN("static, const, templated scalar types")
	{
		REQUIRE(Scalarf::One == 1.0f);
		REQUIRE(Scalarf::Zero == 0.0f);
		REQUIRE(Scalard::One == 1.0);
		REQUIRE(Scalard::Zero == 0.0);
		REQUIRE(Scalari32::One == 1);
		REQUIRE(Scalari32::Zero == 0);
		REQUIRE(Scalaru32::One == 1u);
		REQUIRE(Scalaru32::Zero == 0u);
		REQUIRE(Scalari64::One == 1);
		REQUIRE(Scalari64::Zero == 0);
		REQUIRE(Scalaru64::One == 1u);
		REQUIRE(Scalaru64::Zero == 0u);
		REQUIRE(Scalari16::One == 1);
		REQUIRE(Scalari16::Zero == 0);
		REQUIRE(Scalaru16::One == 1u);
		REQUIRE(Scalaru16::Zero == 0u);
		REQUIRE(Scalari8::One == 1);
		REQUIRE(Scalari8::Zero == 0);
		REQUIRE(Scalaru8::One == 1u);
		REQUIRE(Scalaru8::Zero == 0u);
	}

	GIVEN("scalar variables set to an easily square-rootable value")
	{
		int32 vi32 = 16;
		uint32 vu32 = 16u;
		int64 vi64 = 16;
		uint64 vu64 = 16u;
		int16 vi16 = 16;
		uint16 vu16 = 16u;
		int8 vi8 = 16;
		uint8 vu8 = 16u;
		float vf = 16.0f;
		double vd = 16.0;

		REQUIRE(Sqrt(vi32) == 4);
		REQUIRE(Sqrt(vu32) == 4u);
		REQUIRE(Sqrt(vi64) == 4);
		REQUIRE(Sqrt(vu64) == 4u);
		REQUIRE(Sqrt(vi16) == 4);
		REQUIRE(Sqrt(vu16) == 4u);
		REQUIRE(Sqrt(vi8) == 4);
		REQUIRE(Sqrt(vu8) == 4u);
		REQUIRE(Sqrt(vf) == 4.0f);
		REQUIRE(Sqrt(vd) == 4.0);

		REQUIRE(Min(vi32, 24) == vi32);
		REQUIRE(Min(vu32, 24u) == vu32);
		REQUIRE(Min(vi64, (int64)24) == vi64);
		REQUIRE(Min(vu64, (uint64)24u) == vu64);
		REQUIRE(Min(vi16, (int16)24) == vi16);
		REQUIRE(Min(vu16, (uint16)24u) == vu16);
		REQUIRE(Min(vi8, (int8)24) == vi8);
		REQUIRE(Min(vu8, (uint8)24u) == vu8);
		REQUIRE(Min(vf, 24.0f) == vf);
		REQUIRE(Min(vd, 24.0) == vd);

		REQUIRE(Max(vi32, 8) == vi32);
		REQUIRE(Max(vu32, 8u) == vu32);
		REQUIRE(Max(vi64, (int64)8) == vi64);
		REQUIRE(Max(vu64, (uint64)8u) == vu64);
		REQUIRE(Max(vi16, (int16)8) == vi16);
		REQUIRE(Max(vu16, (uint16)8u) == vu16);
		REQUIRE(Max(vi8, (int8)8) == vi8);
		REQUIRE(Max(vu8, (uint8)8u) == vu8);
		REQUIRE(Max(vf, 8.0f) == vf);
		REQUIRE(Max(vd, 8.0) == vd);
	}
}

SCENARIO("vector2 math produces correct results")
{
	GIVEN("three Vector2f objects")
	{
		Vector2f a;
		Vector2f b(2.0f, 5.0f);
		Vector2f c(b);

		REQUIRE(a == Vector2f::Zero);
		REQUIRE((b.X == 2.0f && b.Y == 5.0f));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector2f(6.0f, 2.5f);
			b = a + Vector2f::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6.0f && a.Y == 2.5f));
				REQUIRE((b.X == 7.0f && b.Y == 3.5f));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector2f::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1.0f && b.Y == 4.0f));
				REQUIRE(a == Vector2f::One);
			}
		}

		WHEN("vector-scalar multiplication is performed")
		{
			a = b * 2.0f;
			b *= 2.0f;
			c = 2.0f * b;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(a == b);
				REQUIRE((c.X == b.X * 2.0f && c.Y == b.Y * 2.0f));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector2f(2.0f, 3.0f);
			b *= Vector2f(2.0f, 3.0f);
			
			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4.0f && a.Y == 15.0f));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			a = 10.0f / b;
			b /= 2.0f;
			c = c / 2.0f;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5.0f && a.Y == 2.0f));
				REQUIRE((b.X == 1.0f && b.Y == 2.5f));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector2f(10.0f, 10.0f) / b;
			b /= Vector2f(1.0f, 2.0f);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5.0f && a.Y == 2.0f));
				REQUIRE((b.X == 2.0f && b.Y == 2.5f));
			}
		}
	}

	GIVEN("an un-normalized vector representing the x-axis")
	{
		Vector2f x(8.0f, 0.0f);

		REQUIRE(x.LengthSq() == 64.0f);

		WHEN("the vector is normalized")
		{
			Vector2f nx = x.Normalized();
			x.Normalize();

			THEN("the normalization produces an x-axis vector, with a length of 1")
			{
				REQUIRE(nx == Vector2f::XAxis);
				REQUIRE(x == nx);
				REQUIRE(x.Length() == 1.0f);
			}

			AND_WHEN("the cross product (2D version) is generated")
			{
				Vector2f xCross = x.Cross();

				THEN("the result should match the y-axis")
				{
					REQUIRE(xCross == Vector2f::YAxis);

					WHEN("the dot product of the result and the x-axis is calculated")
					{
						float t = xCross.Dot(Vector2f::XAxis);

						THEN("the result should be 0")
						{
							REQUIRE(t == 0.0f);
						}
					}
				}
			}
		}
	}

	GIVEN("an un-normalized arbitrary vector")
	{
		Vector2f v(5.0f, 5.0f);

		WHEN("the vector is normalized")
		{
			v.Normalize();

			THEN("the result has a length of 1")
			{
				REQUIRE(Scalarf::Equal(v.Length(), Scalarf::One));
			}
		}

		WHEN("the vector is negated")
		{
			Vector2f neg = -v;

			THEN("the resulting components should be the negative values of the original components")
			{
				REQUIRE(Scalarf::Equal(neg.X, -v.X));
				REQUIRE(Scalarf::Equal(neg.Y, -v.Y));
			}
		}

		WHEN("the vector is projected onto the x-axis")
		{
			Vector2f vp = v.Project(Vector2f::XAxis);

			THEN("the result is correct")
			{
				REQUIRE(vp == Vector2f(5.0f, 0.0f));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector2f v = Vector2f::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}

		WHEN("the multi-byte string representation of the vector is generated")
		{
			MbString str1 = v;
			MbStringStream mbStrStream;
			mbStrStream << v;
			MbString str2 = mbStrStream.str();
			const MbString checkVal = "<1, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}