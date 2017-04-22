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
						float t = xCross.Dot(Vector2d::XAxis);

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
				REQUIRE(vp == Vector2d(5.0f, 0.0f));
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