#include "catch.hpp"
#include "Math/Math.h"
#include "Math/Vector2.h"

using namespace ETL::Math;
using namespace ETL;

//////////////////////////////////////////////////////////////////////////
// Vector2f
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector2 float math produces correct results", "[vector2f]")
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

//////////////////////////////////////////////////////////////////////////
// Vector2d
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector2 double math produces correct results", "[vector2d]")
{
	GIVEN("three Vector2d objects")
	{
		Vector2d a;
		Vector2d b(2.0, 5.0);
		Vector2d c(b);

		REQUIRE(a == Vector2d::Zero);
		REQUIRE((b.X == 2.0 && b.Y == 5.0));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector2d(6.0, 2.5);
			b = a + Vector2d::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6.0 && a.Y == 2.5));
				REQUIRE((b.X == 7.0 && b.Y == 3.5));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector2d::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1.0 && b.Y == 4.0));
				REQUIRE(a == Vector2d::One);
			}
		}

		WHEN("vector-scalar multiplication is performed")
		{
			a = b * 2.0;
			b *= 2.0;
			c = 2.0 * b;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(a == b);
				REQUIRE((c.X == b.X * 2.0 && c.Y == b.Y * 2.0));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector2d(2.0, 3.0);
			b *= Vector2d(2.0, 3.0);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4.0 && a.Y == 15.0));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			a = 10.0 / b;
			b /= 2.0;
			c = c / 2.0;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5.0 && a.Y == 2.0));
				REQUIRE((b.X == 1.0 && b.Y == 2.5));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector2d(10.0, 10.0) / b;
			b /= Vector2d(1.0, 2.0);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5.0 && a.Y == 2.0));
				REQUIRE((b.X == 2.0 && b.Y == 2.5));
			}
		}
	}

	GIVEN("an un-normalized vector representing the x-axis")
	{
		Vector2d x(8.0, 0.0);

		REQUIRE(x.LengthSq() == 64.0);

		WHEN("the vector is normalized")
		{
			Vector2d nx = x.Normalized();
			x.Normalize();

			THEN("the normalization produces an x-axis vector, with a length of 1")
			{
				REQUIRE(nx == Vector2d::XAxis);
				REQUIRE(x == nx);
				REQUIRE(x.Length() == 1.0);
			}

			AND_WHEN("the cross product (2D version) is generated")
			{
				Vector2d xCross = x.Cross();

				THEN("the result should match the y-axis")
				{
					REQUIRE(xCross == Vector2d::YAxis);

					WHEN("the dot product of the result and the x-axis is calculated")
					{
						double t = xCross.Dot(Vector2d::XAxis);

						THEN("the result should be 0")
						{
							REQUIRE(t == 0.0);
						}
					}
				}
			}
		}
	}

	GIVEN("an un-normalized arbitrary vector")
	{
		Vector2d v(5.0, 5.0);

		WHEN("the vector is normalized")
		{
			v.Normalize();

			THEN("the result has a length of 1")
			{
				REQUIRE(Scalard::Equal(v.Length(), Scalard::One));
			}
		}

		WHEN("the vector is negated")
		{
			Vector2d neg = -v;

			THEN("the resulting components should be the negative values of the original components")
			{
				REQUIRE(Scalard::Equal(neg.X, -v.X));
				REQUIRE(Scalard::Equal(neg.Y, -v.Y));
			}
		}

		WHEN("the vector is projected onto the x-axis")
		{
			Vector2d vp = v.Project(Vector2d::XAxis);

			THEN("the result is correct")
			{
				REQUIRE(vp == Vector2d(5.0, 0.0));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector2d v = Vector2d::XAxis;

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

//////////////////////////////////////////////////////////////////////////
// Vector2i32
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector2 32-bit signed integer math produces correct results", "[vector2i32]")
{
	GIVEN("three Vector2i32 objects")
	{
		Vector2i32 a;
		Vector2i32 b(2, 5);
		Vector2i32 c(b);

		REQUIRE(a == Vector2i32::Zero);
		REQUIRE((b.X == 2 && b.Y == 5));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector2i32(6, 2);
			b = a + Vector2i32::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2));
				REQUIRE((b.X == 7 && b.Y == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector2i32::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4));
				REQUIRE(a == Vector2i32::One);
			}
		}

		WHEN("vector-scalar multiplication is performed")
		{
			a = b * 2;
			b *= 2;
			c = 2 * b;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(a == b);
				REQUIRE((c.X == b.X * 2 && c.Y == b.Y * 2));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector2i32(2, 3);
			b *= Vector2i32(2, 3);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			a = 10 / b;
			b /= 2;
			c = c / 2;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2));
				REQUIRE((b.X == 1 && b.Y == 2));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector2i32(10, 10) / b;
			b /= Vector2i32(1, 2);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2));
				REQUIRE((b.X == 2 && b.Y == 2));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector2i32 v = Vector2i32::XAxis;

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

//////////////////////////////////////////////////////////////////////////
// Vector2u32
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector2 32-bit unsigned integer math produces correct results", "[vector2u32]")
{
	GIVEN("three Vector2u32 objects")
	{
		Vector2u32 a;
		Vector2u32 b(2u, 5u);
		Vector2u32 c(b);

		REQUIRE(a == Vector2u32::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector2u32(6u, 2u);
			b = a + Vector2u32::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u));
				REQUIRE((b.X == 7u && b.Y == 3u));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector2u32::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u));
				REQUIRE(a == Vector2u32::One);
			}
		}

		WHEN("vector-scalar multiplication is performed")
		{
			a = b * 2u;
			b *= 2u;
			c = 2u * b;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(a == b);
				REQUIRE((c.X == b.X * 2u && c.Y == b.Y * 2u));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector2u32(2u, 3u);
			b *= Vector2u32(2u, 3u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			a = 10u / b;
			b /= 2u;
			c = c / 2u;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u));
				REQUIRE((b.X == 1u && b.Y == 2u));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector2u32(10u, 10u) / b;
			b /= Vector2u32(1u, 2u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u));
				REQUIRE((b.X == 2u && b.Y == 2u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector2u32 v = Vector2u32::XAxis;

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

//////////////////////////////////////////////////////////////////////////
// Vector2i64
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector2 64-bit signed integer math produces correct results", "[vector2i64]")
{
	GIVEN("three Vector2i64 objects")
	{
		Vector2i64 a;
		Vector2i64 b(2, 5);
		Vector2i64 c(b);

		REQUIRE(a == Vector2i64::Zero);
		REQUIRE((b.X == 2 && b.Y == 5));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector2i64(6, 2);
			b = a + Vector2i64::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2));
				REQUIRE((b.X == 7 && b.Y == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector2i64::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4));
				REQUIRE(a == Vector2i64::One);
			}
		}

		WHEN("vector-scalar multiplication is performed")
		{
			a = b * 2;
			b *= 2;
			c = 2 * b;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(a == b);
				REQUIRE((c.X == b.X * 2 && c.Y == b.Y * 2));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector2i64(2, 3);
			b *= Vector2i64(2, 3);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			a = 10 / b;
			b /= 2;
			c = c / 2;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2));
				REQUIRE((b.X == 1 && b.Y == 2));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector2i64(10, 10) / b;
			b /= Vector2i64(1, 2);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2));
				REQUIRE((b.X == 2 && b.Y == 2));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector2i64 v = Vector2i64::XAxis;

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

//////////////////////////////////////////////////////////////////////////
// Vector2u64
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector2 64-bit unsigned integer math produces correct results", "[vector2u64]")
{
	GIVEN("three Vector2u64 objects")
	{
		Vector2u64 a;
		Vector2u64 b(2u, 5u);
		Vector2u64 c(b);

		REQUIRE(a == Vector2u64::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector2u64(6u, 2u);
			b = a + Vector2u64::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u));
				REQUIRE((b.X == 7u && b.Y == 3u));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector2u64::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u));
				REQUIRE(a == Vector2u64::One);
			}
		}

		WHEN("vector-scalar multiplication is performed")
		{
			a = b * 2u;
			b *= 2u;
			c = 2u * b;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(a == b);
				REQUIRE((c.X == b.X * 2u && c.Y == b.Y * 2u));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector2u64(2u, 3u);
			b *= Vector2u64(2u, 3u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			a = 10u / b;
			b /= 2u;
			c = c / 2u;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u));
				REQUIRE((b.X == 1u && b.Y == 2u));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector2u64(10u, 10u) / b;
			b /= Vector2u64(1u, 2u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u));
				REQUIRE((b.X == 2u && b.Y == 2u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector2u64 v = Vector2u64::XAxis;

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

//////////////////////////////////////////////////////////////////////////
// Vector2i16
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector2 16-bit signed integer math produces correct results", "[vector2i16]")
{
	GIVEN("three Vector2i16 objects")
	{
		Vector2i16 a;
		Vector2i16 b(2, 5);
		Vector2i16 c(b);

		REQUIRE(a == Vector2i16::Zero);
		REQUIRE((b.X == 2 && b.Y == 5));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector2i16(6, 2);
			b = a + Vector2i16::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2));
				REQUIRE((b.X == 7 && b.Y == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector2i16::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4));
				REQUIRE(a == Vector2i16::One);
			}
		}

		WHEN("vector-scalar multiplication is performed")
		{
			a = b * 2;
			b *= 2;
			c = 2 * b;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(a == b);
				REQUIRE((c.X == b.X * 2 && c.Y == b.Y * 2));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector2i16(2, 3);
			b *= Vector2i16(2, 3);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			a = 10 / b;
			b /= 2;
			c = c / 2;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2));
				REQUIRE((b.X == 1 && b.Y == 2));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector2i16(10, 10) / b;
			b /= Vector2i16(1, 2);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2));
				REQUIRE((b.X == 2 && b.Y == 2));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector2i16 v = Vector2i16::XAxis;

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

//////////////////////////////////////////////////////////////////////////
// Vector2u16
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector2 16-bit unsigned integer math produces correct results", "[vector2u16]")
{
	GIVEN("three Vector2u16 objects")
	{
		Vector2u16 a;
		Vector2u16 b(2u, 5u);
		Vector2u16 c(b);

		REQUIRE(a == Vector2u16::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector2u16(6u, 2u);
			b = a + Vector2u16::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u));
				REQUIRE((b.X == 7u && b.Y == 3u));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector2u16::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u));
				REQUIRE(a == Vector2u16::One);
			}
		}

		WHEN("vector-scalar multiplication is performed")
		{
			a = b * 2u;
			b *= 2u;
			c = 2u * b;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(a == b);
				REQUIRE((c.X == b.X * 2u && c.Y == b.Y * 2u));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector2u16(2u, 3u);
			b *= Vector2u16(2u, 3u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			a = 10u / b;
			b /= 2u;
			c = c / 2u;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u));
				REQUIRE((b.X == 1u && b.Y == 2u));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector2u16(10u, 10u) / b;
			b /= Vector2u16(1u, 2u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u));
				REQUIRE((b.X == 2u && b.Y == 2u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector2u16 v = Vector2u16::XAxis;

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

//////////////////////////////////////////////////////////////////////////
// Vector2i8
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector2 8-bit signed integer math produces correct results", "[vector2i8]")
{
	GIVEN("three Vector2i8 objects")
	{
		Vector2i8 a;
		Vector2i8 b(2, 5);
		Vector2i8 c(b);

		REQUIRE(a == Vector2i8::Zero);
		REQUIRE((b.X == 2 && b.Y == 5));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector2i8(6, 2);
			b = a + Vector2i8::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2));
				REQUIRE((b.X == 7 && b.Y == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector2i8::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4));
				REQUIRE(a == Vector2i8::One);
			}
		}

		WHEN("vector-scalar multiplication is performed")
		{
			a = b * 2;
			b *= 2;
			c = 2 * b;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(a == b);
				REQUIRE((c.X == b.X * 2 && c.Y == b.Y * 2));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector2i8(2, 3);
			b *= Vector2i8(2, 3);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			a = 10 / b;
			b /= 2;
			c = c / 2;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2));
				REQUIRE((b.X == 1 && b.Y == 2));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector2i8(10, 10) / b;
			b /= Vector2i8(1, 2);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2));
				REQUIRE((b.X == 2 && b.Y == 2));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector2i8 v = Vector2i8::XAxis;

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

//////////////////////////////////////////////////////////////////////////
// Vector2u8
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector2 8-bit unsigned integer math produces correct results", "[vector2u8]")
{
	GIVEN("three Vector2u8 objects")
	{
		Vector2u8 a;
		Vector2u8 b(2u, 5u);
		Vector2u8 c(b);

		REQUIRE(a == Vector2u8::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector2u8(6u, 2u);
			b = a + Vector2u8::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u));
				REQUIRE((b.X == 7u && b.Y == 3u));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector2u8::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u));
				REQUIRE(a == Vector2u8::One);
			}
		}

		WHEN("vector-scalar multiplication is performed")
		{
			a = b * 2u;
			b *= 2u;
			c = 2u * b;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(a == b);
				REQUIRE((c.X == b.X * 2u && c.Y == b.Y * 2u));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector2u8(2u, 3u);
			b *= Vector2u8(2u, 3u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			a = 10u / b;
			b /= 2u;
			c = c / 2u;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u));
				REQUIRE((b.X == 1u && b.Y == 2u));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector2u8(10u, 10u) / b;
			b /= Vector2u8(1u, 2u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u));
				REQUIRE((b.X == 2u && b.Y == 2u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector2u8 v = Vector2u8::XAxis;

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