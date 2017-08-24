#include "catch.hpp"
#include "Math/Math.h"
#include "Math/Vector4.h"

using namespace ETL::Math;
using namespace ETL;

//////////////////////////////////////////////////////////////////////////
// Vector4f
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector4 float math produces correct results", "[vector4f]")
{
	GIVEN("three Vector4f objects")
	{
		Vector4f a;
		Vector4f b(2.0f, 5.0f, 3.0f);
		Vector4f c(b);

		REQUIRE(a == Vector4f::Zero);
		REQUIRE((b.X == 2.0f && b.Y == 5.0f && b.Z == 3.0f));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector4f(6.0f, 2.5f, 2.0f);
			b = a + Vector4f::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6.0f && a.Y == 2.5f && a.Z == 2.0f));
				REQUIRE((b.X == 7.0f && b.Y == 3.5f && b.Z == 3.0f));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector4f::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1.0f && b.Y == 4.0f && b.Z == 2.0f));
				REQUIRE(a == Vector4f::One);
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
				REQUIRE((c.X == b.X * 2.0f && c.Y == b.Y * 2.0f && c.Z == b.Z * 2.0f));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector4f(2.0f, 3.0f, 2.5f);
			b *= Vector4f(2.0f, 3.0f, 2.5f);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4.0f && a.Y == 15.0f && a.Z == 7.5f));
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
				REQUIRE((a.X == 5.0f && a.Y == 2.0f && Scalar<float>::Equal(a.Z, 10.0f / 3.0f)));
				REQUIRE((b.X == 1.0f && b.Y == 2.5f && b.Z == 1.5f));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector4f(10.0f, 10.0f, 10.0f) / b;
			b /= Vector4f(1.0f, 2.0f, 3.0f);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5.0f && a.Y == 2.0f && Scalar<float>::Equal(a.Z, 10.0f / 3.0f)));
				REQUIRE((b.X == 2.0f && b.Y == 2.5f && b.Z == 1.0f));
			}
		}
	}

	GIVEN("an un-normalized vector representing the x-axis")
	{
		Vector4f x(8.0f, 0.0f, 0.0f);

		REQUIRE(x.LengthSq() == 64.0f);

		WHEN("the vector is normalized")
		{
			Vector4f nx = x.Normalized();
			x.Normalize();

			THEN("the normalization produces an x-axis vector, with a length of 1")
			{
				REQUIRE(nx == Vector4f::XAxis);
				REQUIRE(x == nx);
				REQUIRE(x.Length() == 1.0f);
			}

			AND_WHEN("the cross product of it and a vector representing the y-axis is calculated")
			{
				Vector4f xCross = x.Cross(Vector4f::YAxis);

				THEN("the result should match the z-axis")
				{
					REQUIRE(xCross == Vector4f::ZAxis);

					WHEN("the dot product of the result and the x-axis is calculated")
					{
						float t = xCross.Dot(Vector4f::XAxis);

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
		Vector4f v(5.0f, 5.0f, 5.0f);

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
			Vector4f neg = -v;

			THEN("the resulting components should be the negative values of the original components")
			{
				REQUIRE(Scalarf::Equal(neg.X, -v.X));
				REQUIRE(Scalarf::Equal(neg.Y, -v.Y));
				REQUIRE(Scalarf::Equal(neg.Z, -v.Z));
			}
		}

		WHEN("the vector is projected onto the x-axis")
		{
			Vector4f vp = v.Project(Vector4f::XAxis);

			THEN("the result is correct")
			{
				REQUIRE(vp == Vector4f(5.0f, 0.0f, 0.0f));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector4f v = Vector4f::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector4d
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector4 double math produces correct results", "[vector4d]")
{
	GIVEN("three Vector4d objects")
	{
		Vector4d a;
		Vector4d b(2.0, 5.0, 3.0);
		Vector4d c(b);

		REQUIRE(a == Vector4d::Zero);
		REQUIRE((b.X == 2.0 && b.Y == 5.0 && b.Z == 3.0));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector4d(6.0, 2.5, 2.0);
			b = a + Vector4d::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6.0 && a.Y == 2.5 && a.Z == 2.0f));
				REQUIRE((b.X == 7.0 && b.Y == 3.5 && b.Z == 3.0f));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector4d::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1.0 && b.Y == 4.0 && b.Z == 2.0));
				REQUIRE(a == Vector4d::One);
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
				REQUIRE((c.X == b.X * 2.0 && c.Y == b.Y * 2.0 && c.Z == b.Z * 2.0));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector4d(2.0, 3.0, 2.5);
			b *= Vector4d(2.0, 3.0, 2.5);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4.0 && a.Y == 15.0 && a.Z == 7.5));
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
				REQUIRE((a.X == 5.0 && a.Y == 2.0 && Scalar<double>::Equal(a.Z, 10.0 / 3.0)));
				REQUIRE((b.X == 1.0 && b.Y == 2.5 && b.Z == 1.5));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector4d(10.0, 10.0, 10.0) / b;
			b /= Vector4d(1.0, 2.0, 3.0);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5.0 && a.Y == 2.0 && Scalar<double>::Equal(a.Z, 10.0 / 3.0)));
				REQUIRE((b.X == 2.0 && b.Y == 2.5 && b.Z == 1.0));
			}
		}
	}

	GIVEN("an un-normalized vector representing the x-axis")
	{
		Vector4d x(8.0, 0.0, 0.0);

		REQUIRE(x.LengthSq() == 64.0);

		WHEN("the vector is normalized")
		{
			Vector4d nx = x.Normalized();
			x.Normalize();

			THEN("the normalization produces an x-axis vector, with a length of 1")
			{
				REQUIRE(nx == Vector4d::XAxis);
				REQUIRE(x == nx);
				REQUIRE(x.Length() == 1.0);
			}

			AND_WHEN("the cross product of it and a vector representing the y-axis is calculated")
			{
				Vector4d xCross = x.Cross(Vector4d::YAxis);

				THEN("the result should match the z-axis")
				{
					REQUIRE(xCross == Vector4d::ZAxis);

					WHEN("the dot product of the result and the x-axis is calculated")
					{
						double t = xCross.Dot(Vector4d::XAxis);

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
		Vector4d v(5.0, 5.0, 5.0);

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
			Vector4d neg = -v;

			THEN("the resulting components should be the negative values of the original components")
			{
				REQUIRE(Scalard::Equal(neg.X, -v.X));
				REQUIRE(Scalard::Equal(neg.Y, -v.Y));
				REQUIRE(Scalard::Equal(neg.Z, -v.Z));
			}
		}

		WHEN("the vector is projected onto the x-axis")
		{
			Vector4d vp = v.Project(Vector4d::XAxis);

			THEN("the result is correct")
			{
				REQUIRE(vp == Vector4d(5.0, 0.0, 0.0));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector4d v = Vector4d::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector4i32
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector4 32-bit signed integer math produces correct results", "[vector4i32]")
{
	GIVEN("three Vector4i32 objects")
	{
		Vector4i32 a;
		Vector4i32 b(2, 5, 3);
		Vector4i32 c(b);

		REQUIRE(a == Vector4i32::Zero);
		REQUIRE((b.X == 2 && b.Y == 5 && b.Z == 3));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector4i32(6, 2, 2);
			b = a + Vector4i32::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2 && a.Z == 2));
				REQUIRE((b.X == 7 && b.Y == 3 && b.Z == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector4i32::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4 && b.Z == 2));
				REQUIRE(a == Vector4i32::One);
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
				REQUIRE((c.X == b.X * 2 && c.Y == b.Y * 2 && c.Z == b.Z * 2));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector4i32(2, 3, 2);
			b *= Vector4i32(2, 3, 2);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15 && b.Z == 6));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			b.W = 1;
			a = 10 / b;
			b.W = 0;
			b /= 2;
			c = c / 2;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 1 && b.Y == 2 && b.Z == 1));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			b.W = 1;
			a = Vector4i32(10, 10, 10) / b;
			b.W = 0;
			b /= Vector4i32(1, 2, 3, 1);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 2 && b.Y == 2 && b.Z == 1));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector4i32 v = Vector4i32::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector4u32
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector4 32-bit unsigned integer math produces correct results", "[vector4u32]")
{
	GIVEN("three Vector4u32 objects")
	{
		Vector4u32 a;
		Vector4u32 b(2u, 5u, 3u);
		Vector4u32 c(b);

		REQUIRE(a == Vector4u32::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u && b.Z == 3u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector4u32(6u, 2u, 2u);
			b = a + Vector4u32::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u && a.Z == 2u));
				REQUIRE((b.X == 7u && b.Y == 3u && b.Z == 3u));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector4u32::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u && b.Z == 2u));
				REQUIRE(a == Vector4u32::One);
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
				REQUIRE((c.X == b.X * 2u && c.Y == b.Y * 2u && c.Z == b.Z * 2u));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector4u32(2u, 3u, 2u);
			b *= Vector4u32(2u, 3u, 2u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u && a.Z == 6u));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			b.W = 1u;
			a = 10u / b;
			b.W = 0u;
			b /= 2u;
			c = c / 2u;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 1u && b.Y == 2u && b.Z == 1u));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			b.W = 1u;
			a = Vector4u32(10u, 10u, 10u) / b;
			b.W = 0u;
			b /= Vector4u32(1u, 2u, 3u, 1u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 2u && b.Y == 2u && b.Z == 1u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector4u32 v = Vector4u32::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector4i64
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector4 64-bit signed integer math produces correct results", "[vector4i64]")
{
	GIVEN("three Vector4i64 objects")
	{
		Vector4i64 a;
		Vector4i64 b(2, 5, 3);
		Vector4i64 c(b);

		REQUIRE(a == Vector4i64::Zero);
		REQUIRE((b.X == 2 && b.Y == 5 && b.Z == 3));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector4i64(6, 2, 2);
			b = a + Vector4i64::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2 && a.Z == 2));
				REQUIRE((b.X == 7 && b.Y == 3 && b.Z == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector4i64::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4 && b.Z == 2));
				REQUIRE(a == Vector4i64::One);
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
				REQUIRE((c.X == b.X * 2 && c.Y == b.Y * 2 && c.Z == b.Z * 2));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector4i64(2, 3, 2);
			b *= Vector4i64(2, 3, 2);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15 && a.Z == 6));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			b.W = 1;
			a = 10 / b;
			b.W = 0;
			b /= 2;
			c = c / 2;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 1 && b.Y == 2 && b.Z == 1));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			b.W = 1;
			a = Vector4i64(10, 10, 10) / b;
			b.W = 0;
			b /= Vector4i64(1, 2, 3, 1);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 2 && b.Y == 2 && b.Z == 1));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector4i64 v = Vector4i64::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector4u64
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector4 64-bit unsigned integer math produces correct results", "[vector4u64]")
{
	GIVEN("three Vector4u64 objects")
	{
		Vector4u64 a;
		Vector4u64 b(2u, 5u, 3u);
		Vector4u64 c(b);

		REQUIRE(a == Vector4u64::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u && b.Z == 3u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector4u64(6u, 2u, 2u);
			b = a + Vector4u64::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u && a.Z == 2u));
				REQUIRE((b.X == 7u && b.Y == 3u && b.Z == 3u));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector4u64::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u && b.Z == 2u));
				REQUIRE(a == Vector4u64::One);
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
				REQUIRE((c.X == b.X * 2u && c.Y == b.Y * 2u && c.Z == b.Z * 2u));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector4u64(2u, 3u, 2u);
			b *= Vector4u64(2u, 3u, 2u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u && a.Z == 6u));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			b.W = 1u;
			a = 10u / b;
			b.W = 0u;
			b /= 2u;
			c = c / 2u;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3));
				REQUIRE((b.X == 1u && b.Y == 2u && b.Z == 1));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			b.W = 1u;
			a = Vector4u64(10u, 10u, 10u) / b;
			b.W = 0u;
			b /= Vector4u64(1u, 2u, 3u, 1u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 2u && b.Y == 2u && b.Z == 1u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector4u64 v = Vector4u64::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector4i16
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector4 16-bit signed integer math produces correct results", "[vector4i16]")
{
	GIVEN("three Vector4i16 objects")
	{
		Vector4i16 a;
		Vector4i16 b(2, 5, 3);
		Vector4i16 c(b);

		REQUIRE(a == Vector4i16::Zero);
		REQUIRE((b.X == 2 && b.Y == 5 && b.Z == 3));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector4i16(6, 2, 2);
			b = a + Vector4i16::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2 && a.Z == 2));
				REQUIRE((b.X == 7 && b.Y == 3 && b.Z == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector4i16::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4 && b.Z == 2));
				REQUIRE(a == Vector4i16::One);
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
				REQUIRE((c.X == b.X * 2 && c.Y == b.Y * 2 && c.Z == b.Z * 2));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector4i16(2, 3, 2);
			b *= Vector4i16(2, 3, 2);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15 && a.Z == 6));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			b.W = 1;
			a = 10 / b;
			b.W = 0;
			b /= 2;
			c = c / 2;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 1 && b.Y == 2 && b.Z == 1));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			b.W = 1;
			a = Vector4i16(10, 10, 10) / b;
			b.W = 0;
			b /= Vector4i16(1, 2, 3, 1);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 2 && b.Y == 2 && b.Z == 1));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector4i16 v = Vector4i16::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector4u16
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector4 16-bit unsigned integer math produces correct results", "[vector4u16]")
{
	GIVEN("three Vector4u16 objects")
	{
		Vector4u16 a;
		Vector4u16 b(2u, 5u, 3u);
		Vector4u16 c(b);

		REQUIRE(a == Vector4u16::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u && b.Z == 3u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector4u16(6u, 2u, 2u);
			b = a + Vector4u16::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u && a.Z == 2));
				REQUIRE((b.X == 7u && b.Y == 3u && b.Z == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector4u16::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u && b.Z == 2u));
				REQUIRE(a == Vector4u16::One);
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
				REQUIRE((c.X == b.X * 2u && c.Y == b.Y * 2u && c.Z == b.Z * 2u));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector4u16(2u, 3u, 2u);
			b *= Vector4u16(2u, 3u, 2u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u && a.Z == 6u));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			b.W = 1u;
			a = 10u / b;
			b.W = 0u;
			b /= 2u;
			c = c / 2u;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 1u && b.Y == 2u && b.Z == 1u));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			b.W = 1u;
			a = Vector4u16(10u, 10u, 10u) / b;
			b.W = 0u;
			b /= Vector4u16(1u, 2u, 3u, 1u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 2u && b.Y == 2u && b.Z == 1u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector4u16 v = Vector4u16::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector4i8
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector4 8-bit signed integer math produces correct results", "[vector4i8]")
{
	GIVEN("three Vector4i8 objects")
	{
		Vector4i8 a;
		Vector4i8 b(2, 5, 3);
		Vector4i8 c(b);

		REQUIRE(a == Vector4i8::Zero);
		REQUIRE((b.X == 2 && b.Y == 5 && b.Z == 3));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector4i8(6, 2, 2);
			b = a + Vector4i8::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2 && a.Z == 2));
				REQUIRE((b.X == 7 && b.Y == 3 && b.Z == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector4i8::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4 && b.Z == 2));
				REQUIRE(a == Vector4i8::One);
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
				REQUIRE((c.X == b.X * 2 && c.Y == b.Y * 2 && c.Z == b.Z * 2));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector4i8(2, 3, 2);
			b *= Vector4i8(2, 3, 2);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15 && a.Z == 6));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			b.W = 1;
			a = 10 / b;
			b.W = 0;
			b /= 2;
			c = c / 2;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 1 && b.Y == 2 && b.Z == 1));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			b.W = 1;
			a = Vector4i8(10, 10, 10) / b;
			b.W = 0;
			b /= Vector4i8(1, 2, 3, 1);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 2 && b.Y == 2 && b.Z == 1));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector4i8 v = Vector4i8::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector4u8
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector4 8-bit unsigned integer math produces correct results", "[vector4u8]")
{
	GIVEN("three Vector4u8 objects")
	{
		Vector4u8 a;
		Vector4u8 b(2u, 5u, 3u);
		Vector4u8 c(b);

		REQUIRE(a == Vector4u8::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u && b.Z == 3u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector4u8(6u, 2u, 2u);
			b = a + Vector4u8::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u && a.Z == 2u));
				REQUIRE((b.X == 7u && b.Y == 3u && b.Z == 3u));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector4u8::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u && b.Z == 2u));
				REQUIRE(a == Vector4u8::One);
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
				REQUIRE((c.X == b.X * 2u && c.Y == b.Y * 2u && c.Z == b.Z * 2u));
			}
		}

		WHEN("vector-vector multiplication is performed")
		{
			a = b * Vector4u8(2u, 3u, 2u);
			b *= Vector4u8(2u, 3u, 2u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u && a.Z == 6u));
				REQUIRE(a == b);
			}
		}

		WHEN("vector-scalar division is performed")
		{
			b.W = 1u;
			a = 10u / b;
			b.W = 0u;
			b /= 2u;
			c = c / 2u;

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 1u && b.Y == 2u && b.Z == 1u));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			b.W = 1u;
			a = Vector4u8(10u, 10u, 10u) / b;
			b.W = 0u;
			b /= Vector4u8(1u, 2u, 3u, 1u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 2u && b.Y == 2u && b.Z == 1u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector4u8 v = Vector4u8::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}