#include "catch.hpp"
#include "Math/Math.h"
#include "Math/Vector3.h"

using namespace ETL::Math;
using namespace ETL;

//////////////////////////////////////////////////////////////////////////
// Vector3f
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector3 float math produces correct results", "[vector3f]")
{
	GIVEN("three Vector3f objects")
	{
		Vector3f a;
		Vector3f b(2.0f, 5.0f, 3.0f);
		Vector3f c(b);

		REQUIRE(a == Vector3f::Zero);
		REQUIRE((b.X == 2.0f && b.Y == 5.0f && b.Z == 3.0f));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector3f(6.0f, 2.5f, 2.0f);
			b = a + Vector3f::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6.0f && a.Y == 2.5f && a.Z == 2.0f));
				REQUIRE((b.X == 7.0f && b.Y == 3.5f && b.Z == 3.0f));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector3f::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1.0f && b.Y == 4.0f && b.Z == 2.0f));
				REQUIRE(a == Vector3f::One);
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
			a = b * Vector3f(2.0f, 3.0f, 2.5f);
			b *= Vector3f(2.0f, 3.0f, 2.5f);

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
			a = Vector3f(10.0f, 10.0f, 10.0f) / b;
			b /= Vector3f(1.0f, 2.0f, 3.0f);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5.0f && a.Y == 2.0f && Scalar<float>::Equal(a.Z, 10.0f / 3.0f)));
				REQUIRE((b.X == 2.0f && b.Y == 2.5f && b.Z == 1.0f));
			}
		}
	}

	GIVEN("an un-normalized vector representing the x-axis")
	{
		Vector3f x(8.0f, 0.0f, 0.0f);

		REQUIRE(x.LengthSq() == 64.0f);

		WHEN("the vector is normalized")
		{
			Vector3f nx = x.Normalized();
			x.Normalize();

			THEN("the normalization produces an x-axis vector, with a length of 1")
			{
				REQUIRE(nx == Vector3f::XAxis);
				REQUIRE(x == nx);
				REQUIRE(x.Length() == 1.0f);
			}

			AND_WHEN("the cross product of it and a vector representing the y-axis is calculated")
			{
				Vector3f xCross = x.Cross(Vector3f::YAxis);

				THEN("the result should match the z-axis")
				{
					REQUIRE(xCross == Vector3f::ZAxis);

					WHEN("the dot product of the result and the x-axis is calculated")
					{
						float t = xCross.Dot(Vector3f::XAxis);

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
		Vector3f v(5.0f, 5.0f, 5.0f);

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
			Vector3f neg = -v;

			THEN("the resulting components should be the negative values of the original components")
			{
				REQUIRE(Scalarf::Equal(neg.X, -v.X));
				REQUIRE(Scalarf::Equal(neg.Y, -v.Y));
				REQUIRE(Scalarf::Equal(neg.Z, -v.Z));
			}
		}

		WHEN("the vector is projected onto the x-axis")
		{
			Vector3f vp = v.Project(Vector3f::XAxis);

			THEN("the result is correct")
			{
				REQUIRE(vp == Vector3f(5.0f, 0.0f, 0.0f));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector3f v = Vector3f::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector3d
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector3 double math produces correct results", "[vector3d]")
{
	GIVEN("three Vector3d objects")
	{
		Vector3d a;
		Vector3d b(2.0, 5.0, 3.0);
		Vector3d c(b);

		REQUIRE(a == Vector3d::Zero);
		REQUIRE((b.X == 2.0 && b.Y == 5.0 && b.Z == 3.0));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector3d(6.0, 2.5, 2.0);
			b = a + Vector3d::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6.0 && a.Y == 2.5 && a.Z == 2.0f));
				REQUIRE((b.X == 7.0 && b.Y == 3.5 && b.Z == 3.0f));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector3d::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1.0 && b.Y == 4.0 && b.Z == 2.0));
				REQUIRE(a == Vector3d::One);
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
			a = b * Vector3d(2.0, 3.0, 2.5);
			b *= Vector3d(2.0, 3.0, 2.5);

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
			a = Vector3d(10.0, 10.0, 10.0) / b;
			b /= Vector3d(1.0, 2.0, 3.0);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5.0 && a.Y == 2.0 && Scalar<double>::Equal(a.Z, 10.0 / 3.0)));
				REQUIRE((b.X == 2.0 && b.Y == 2.5 && b.Z == 1.0));
			}
		}
	}

	GIVEN("an un-normalized vector representing the x-axis")
	{
		Vector3d x(8.0, 0.0, 0.0);

		REQUIRE(x.LengthSq() == 64.0);

		WHEN("the vector is normalized")
		{
			Vector3d nx = x.Normalized();
			x.Normalize();

			THEN("the normalization produces an x-axis vector, with a length of 1")
			{
				REQUIRE(nx == Vector3d::XAxis);
				REQUIRE(x == nx);
				REQUIRE(x.Length() == 1.0);
			}

			AND_WHEN("the cross product of it and a vector representing the y-axis is calculated")
			{
				Vector3d xCross = x.Cross(Vector3d::YAxis);

				THEN("the result should match the z-axis")
				{
					REQUIRE(xCross == Vector3d::ZAxis);

					WHEN("the dot product of the result and the x-axis is calculated")
					{
						double t = xCross.Dot(Vector3d::XAxis);

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
		Vector3d v(5.0, 5.0, 5.0);

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
			Vector3d neg = -v;

			THEN("the resulting components should be the negative values of the original components")
			{
				REQUIRE(Scalard::Equal(neg.X, -v.X));
				REQUIRE(Scalard::Equal(neg.Y, -v.Y));
				REQUIRE(Scalard::Equal(neg.Z, -v.Z));
			}
		}

		WHEN("the vector is projected onto the x-axis")
		{
			Vector3d vp = v.Project(Vector3d::XAxis);

			THEN("the result is correct")
			{
				REQUIRE(vp == Vector3d(5.0, 0.0, 0.0));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector3d v = Vector3d::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector3i32
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector3 32-bit signed integer math produces correct results", "[vector3i32]")
{
	GIVEN("three Vector3i32 objects")
	{
		Vector3i32 a;
		Vector3i32 b(2, 5, 3);
		Vector3i32 c(b);

		REQUIRE(a == Vector3i32::Zero);
		REQUIRE((b.X == 2 && b.Y == 5 && b.Z == 3));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector3i32(6, 2, 2);
			b = a + Vector3i32::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2 && a.Z == 2));
				REQUIRE((b.X == 7 && b.Y == 3 && b.Z == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector3i32::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4 && b.Z == 2));
				REQUIRE(a == Vector3i32::One);
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
			a = b * Vector3i32(2, 3, 2);
			b *= Vector3i32(2, 3, 2);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15 && b.Z == 6));
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
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 1 && b.Y == 2 && b.Z == 1));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector3i32(10, 10, 10) / b;
			b /= Vector3i32(1, 2, 3);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 2 && b.Y == 2 && b.Z == 1));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector3i32 v = Vector3i32::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector3u32
//////////////////////////////////////////////////////////////////////////
SCENARIO("Vector3 32-bit unsigned integer math produces correct results", "[vector3u32]")
{
	GIVEN("three Vector3u32 objects")
	{
		Vector3u32 a;
		Vector3u32 b(2u, 5u, 3u);
		Vector3u32 c(b);

		REQUIRE(a == Vector3u32::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u && b.Z == 3u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector3u32(6u, 2u, 2u);
			b = a + Vector3u32::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u && a.Z == 2u));
				REQUIRE((b.X == 7u && b.Y == 3u && b.Z == 3u));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector3u32::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u && b.Z == 2u));
				REQUIRE(a == Vector3u32::One);
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
			a = b * Vector3u32(2u, 3u, 2u);
			b *= Vector3u32(2u, 3u, 2u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u && a.Z == 6u));
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
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 1u && b.Y == 2u && b.Z == 1u));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector3u32(10u, 10u, 10u) / b;
			b /= Vector3u32(1u, 2u, 3u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 2u && b.Y == 2u && b.Z == 1u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector3u32 v = Vector3u32::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector3i64
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector3 64-bit signed integer math produces correct results", "[vector3i64]")
{
	GIVEN("three Vector3i64 objects")
	{
		Vector3i64 a;
		Vector3i64 b(2, 5, 3);
		Vector3i64 c(b);

		REQUIRE(a == Vector3i64::Zero);
		REQUIRE((b.X == 2 && b.Y == 5 && b.Z == 3));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector3i64(6, 2, 2);
			b = a + Vector3i64::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2 && a.Z == 2));
				REQUIRE((b.X == 7 && b.Y == 3 && b.Z == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector3i64::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4 && b.Z == 2));
				REQUIRE(a == Vector3i64::One);
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
			a = b * Vector3i64(2, 3, 2);
			b *= Vector3i64(2, 3, 2);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15 && a.Z == 6));
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
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 1 && b.Y == 2 && b.Z == 1));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector3i64(10, 10, 10) / b;
			b /= Vector3i64(1, 2, 3);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 2 && b.Y == 2 && b.Z == 1));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector3i64 v = Vector3i64::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector3u64
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector3 64-bit unsigned integer math produces correct results", "[vector3u64]")
{
	GIVEN("three Vector3u64 objects")
	{
		Vector3u64 a;
		Vector3u64 b(2u, 5u, 3u);
		Vector3u64 c(b);

		REQUIRE(a == Vector3u64::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u && b.Z == 3u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector3u64(6u, 2u, 2u);
			b = a + Vector3u64::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u && a.Z == 2u));
				REQUIRE((b.X == 7u && b.Y == 3u && b.Z == 3u));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector3u64::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u && b.Z == 2u));
				REQUIRE(a == Vector3u64::One);
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
			a = b * Vector3u64(2u, 3u, 2u);
			b *= Vector3u64(2u, 3u, 2u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u && a.Z == 6u));
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
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3));
				REQUIRE((b.X == 1u && b.Y == 2u && b.Z == 1));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector3u64(10u, 10u, 10u) / b;
			b /= Vector3u64(1u, 2u, 3u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 2u && b.Y == 2u && b.Z == 1u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector3u64 v = Vector3u64::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector3i16
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector3 16-bit signed integer math produces correct results", "[vector3i16]")
{
	GIVEN("three Vector3i16 objects")
	{
		Vector3i16 a;
		Vector3i16 b(2, 5, 3);
		Vector3i16 c(b);

		REQUIRE(a == Vector3i16::Zero);
		REQUIRE((b.X == 2 && b.Y == 5 && b.Z == 3));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector3i16(6, 2, 2);
			b = a + Vector3i16::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2 && a.Z == 2));
				REQUIRE((b.X == 7 && b.Y == 3 && b.Z == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector3i16::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4 && b.Z == 2));
				REQUIRE(a == Vector3i16::One);
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
			a = b * Vector3i16(2, 3, 2);
			b *= Vector3i16(2, 3, 2);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15 && a.Z == 6));
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
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 1 && b.Y == 2 && b.Z == 1));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector3i16(10, 10, 10) / b;
			b /= Vector3i16(1, 2, 3);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 2 && b.Y == 2 && b.Z == 1));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector3i16 v = Vector3i16::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector3u16
//////////////////////////////////////////////////////////////////////////
SCENARIO("Vector3 16-bit unsigned integer math produces correct results", "[Vector3u16]")
{
	GIVEN("three Vector3u16 objects")
	{
		Vector3u16 a;
		Vector3u16 b(2u, 5u, 3u);
		Vector3u16 c(b);

		REQUIRE(a == Vector3u16::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u && b.Z == 3u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector3u16(6u, 2u, 2u);
			b = a + Vector3u16::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u && a.Z == 2));
				REQUIRE((b.X == 7u && b.Y == 3u && b.Z == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector3u16::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u && b.Z == 2u));
				REQUIRE(a == Vector3u16::One);
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
			a = b * Vector3u16(2u, 3u, 2u);
			b *= Vector3u16(2u, 3u, 2u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u && a.Z == 6u));
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
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 1u && b.Y == 2u && b.Z == 1u));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector3u16(10u, 10u, 10u) / b;
			b /= Vector3u16(1u, 2u, 3u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 2u && b.Y == 2u && b.Z == 1u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector3u16 v = Vector3u16::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector3i8
//////////////////////////////////////////////////////////////////////////
SCENARIO("Vector3 8-bit signed integer math produces correct results", "[vector3i8]")
{
	GIVEN("three Vector3i8 objects")
	{
		Vector3i8 a;
		Vector3i8 b(2, 5, 3);
		Vector3i8 c(b);

		REQUIRE(a == Vector3i8::Zero);
		REQUIRE((b.X == 2 && b.Y == 5 && b.Z == 3));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector3i8(6, 2, 2);
			b = a + Vector3i8::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6 && a.Y == 2 && a.Z == 2));
				REQUIRE((b.X == 7 && b.Y == 3 && b.Z == 3));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector3i8::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1 && b.Y == 4 && b.Z == 2));
				REQUIRE(a == Vector3i8::One);
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
			a = b * Vector3i8(2, 3, 2);
			b *= Vector3i8(2, 3, 2);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4 && a.Y == 15 && a.Z == 6));
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
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 1 && b.Y == 2 && b.Z == 1));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector3i8(10, 10, 10) / b;
			b /= Vector3i8(1, 2, 3);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5 && a.Y == 2 && a.Z == 3));
				REQUIRE((b.X == 2 && b.Y == 2 && b.Z == 1));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector3i8 v = Vector3i8::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Vector3u8
//////////////////////////////////////////////////////////////////////////
SCENARIO("vector3 8-bit unsigned integer math produces correct results", "[vector3u8]")
{
	GIVEN("three Vector3u8 objects")
	{
		Vector3u8 a;
		Vector3u8 b(2u, 5u, 3u);
		Vector3u8 c(b);

		REQUIRE(a == Vector3u8::Zero);
		REQUIRE((b.X == 2u && b.Y == 5u && b.Z == 3u));
		REQUIRE(a != b);
		REQUIRE(c == b);

		WHEN("vector addition is performed")
		{
			a += Vector3u8(6u, 2u, 2u);
			b = a + Vector3u8::One;

			THEN("the addition is performed correctly")
			{
				REQUIRE((a.X == 6u && a.Y == 2u && a.Z == 2u));
				REQUIRE((b.X == 7u && b.Y == 3u && b.Z == 3u));
			}
		}

		WHEN("vector subtraction is performed")
		{
			b -= Vector3u8::One;
			a = c - b;

			THEN("the subtraction is performed correctly")
			{
				REQUIRE((b.X == 1u && b.Y == 4u && b.Z == 2u));
				REQUIRE(a == Vector3u8::One);
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
			a = b * Vector3u8(2u, 3u, 2u);
			b *= Vector3u8(2u, 3u, 2u);

			THEN("the multiplication is performed correctly")
			{
				REQUIRE((a.X == 4u && a.Y == 15u && a.Z == 6u));
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
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 1u && b.Y == 2u && b.Z == 1u));
				REQUIRE(c == b);
			}
		}

		WHEN("vector-vector division is performed")
		{
			a = Vector3u8(10u, 10u, 10u) / b;
			b /= Vector3u8(1u, 2u, 3u);

			THEN("the division is performed correctly")
			{
				REQUIRE((a.X == 5u && a.Y == 2u && a.Z == 3u));
				REQUIRE((b.X == 2u && b.Y == 2u && b.Z == 1u));
			}
		}
	}

	GIVEN("a normalized vector representing the x-axis")
	{
		Vector3u8 v = Vector3u8::XAxis;

		WHEN("the wide string representation of the vector is generated")
		{
			WideString str1 = v;
			WideStringStream wStrStream;
			wStrStream << v;
			WideString str2 = wStrStream.str();
			const WideString checkVal = L"<1, 0, 0>";

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
			const MbString checkVal = "<1, 0, 0>";

			THEN("the string representation should be accurate")
			{
				REQUIRE(str1 == checkVal);
				REQUIRE(str2 == checkVal);
			}
		}
	}
}