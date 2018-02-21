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
		const float m00 = 1.0f, m01 = 2.0f, m02 = 3.0f, m03 = 4.0f;
		const float m10 = 5.0f, m11 = 6.0f, m12 = 7.0f, m13 = 8.0f;
		const float m20 = 9.0f, m21 = 10.0f, m22 = 11.0f, m23 = 12.0f;
		const float m30 = 13.0f, m31 = 14.0f, m32 = 15.0f, m33 = 16.0f;
		const float kAdd = 1.0f, kMul = 3.0f;

		Matrix4x4f a;
#if ETL_D3D_MATRIX
		Matrix4x4f b(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
#else // ETL_D3D_MATRIX
		Matrix4x4f b(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
#endif // ETL_D3D_MATRIX
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
				REQUIRE((b.M00 == m00 + kAdd && b.M01 == m01 + kAdd && b.M02 == m02 + kAdd && b.M03 == m03 + kAdd
					&& b.M10 == m10 + kAdd && b.M11 == m11 + kAdd && b.M12 == m12 + kAdd && b.M13 == m13 + kAdd
					&& b.M20 == m20 + kAdd && b.M21 == m21 + kAdd && b.M22 == m22 + kAdd && b.M23 == m23 + kAdd
					&& b.M30 == m30 + kAdd && b.M31 == m31 + kAdd && b.M32 == m32 + kAdd && b.M33 == m33 + kAdd));
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
				REQUIRE((b.M00 == m00 - kAdd && b.M01 == m01 - kAdd && b.M02 == m02 - kAdd && b.M03 == m03 - kAdd
					&& b.M10 == m10 - kAdd && b.M11 == m11 - kAdd && b.M12 == m12 - kAdd && b.M13 == m13 - kAdd
					&& b.M20 == m20 - kAdd && b.M21 == m21 - kAdd && b.M22 == m22 - kAdd && b.M23 == m23 - kAdd
					&& b.M30 == m30 - kAdd && b.M31 == m31 - kAdd && b.M32 == m32 - kAdd && b.M33 == m33 - kAdd));
			}
		}

		WHEN("matrix-scalar multiplication is performed")
		{
			b = b * kMul;
			c *= kMul;
			THEN("the multiplication is performed correctly")
			{
				REQUIRE(b == c);
				REQUIRE((b.M00 == m00 * kMul && b.M01 == m01 * kMul && b.M02 == m02 * kMul && b.M03 == m03 * kMul
					&& b.M10 == m10 * kMul && b.M11 == m11 * kMul && b.M12 == m12 * kMul && b.M13 == m13 * kMul
					&& b.M20 == m20 * kMul && b.M21 == m21 * kMul && b.M22 == m22 * kMul && b.M23 == m23 * kMul
					&& b.M30 == m30 * kMul && b.M31 == m31 * kMul && b.M32 == m32 * kMul && b.M33 == m33 * kMul));
			}
		}

		WHEN("matrix-scalar division is performed")
		{
			b = b / kMul;
			c /= kMul;
			THEN("the multiplication is performed correctly")
			{
				REQUIRE(b == c);
				REQUIRE((b.M00 == m00 / kMul && b.M01 == m01 / kMul && b.M02 == m02 / kMul && b.M03 == m03 / kMul
					&& b.M10 == m10 / kMul && b.M11 == m11 / kMul && b.M12 == m12 / kMul && b.M13 == m13 / kMul
					&& b.M20 == m20 / kMul && b.M21 == m21 / kMul && b.M22 == m22 / kMul && b.M23 == m23 / kMul
					&& b.M30 == m30 / kMul && b.M31 == m31 / kMul && b.M32 == m32 / kMul && b.M33 == m33 / kMul));
			}
		}

		WHEN("matrix-matrix multiplication is performed")
		{
#if ETL_D3D_MATRIX
			Vector4f c0(m00, m10, m20, m30);
			Vector4f c1(m01, m11, m21, m31);
			Vector4f c2(m02, m12, m22, m32);
			Vector4f c3(m03, m13, m23, m33);
#else // ETL_D3D_MATRIX
			Vector4f c0(m00, m01, m02, m03);
			Vector4f c1(m10, m11, m12, m13);
			Vector4f c2(m20, m21, m22, m23);
			Vector4f c3(m30, m31, m32, m33);
#endif // ETL_D3D_MATRIX

			Matrix4x4f d(b.X.Dot(c0), b.X.Dot(c1), b.X.Dot(c2), b.X.Dot(c3)
				, b.Y.Dot(c0), b.Y.Dot(c1), b.Y.Dot(c2), b.Y.Dot(c3)
				, b.Z.Dot(c0), b.Z.Dot(c1), b.Z.Dot(c2), b.Z.Dot(c3)
				, b.W.Dot(c0), b.W.Dot(c1), b.W.Dot(c2), b.W.Dot(c3));

			Matrix4x4f e = b * c;
			b *= a;

			THEN("the multiplication is performed correctly")
			{
				REQUIRE(b == c);
				REQUIRE(e == d);
			}
		}

		GIVEN("a rotation matrix, a scaling matrix, a translation matrix, and a vector representing a point")
		{
			const float kPVal = 1.0f;
			const float kScale = 2.0f;
			Matrix4x4f rotation = Matrix4x4f::MakeRotationZ(Scalar<float>::PiOver2); // quarter turn
			Matrix4x4f scale = Matrix4x4f::MakeScale(kScale);
			Matrix4x4f translation = Matrix4x4f::MakeTranslation(Vector3f(kPVal, 0.0f, 0.0f));
			Vector3f point(0.0f, kPVal, 0.0f);

			WHEN("the point is transformed by the rotation")
			{
				point = rotation.Transform(point);

				THEN("the rotation is performed correctly")
				{
					REQUIRE(point == Vector3f(kPVal, 0.0f, 0.0f));
				}
			}

			WHEN("the point is transformed by the translation")
			{
				point = translation.Transform(point);

				THEN("the translation is performed correctly")
				{
					REQUIRE(point == Vector3f(kPVal, kPVal, 0.0f));
				}
			}
		}
	}
}