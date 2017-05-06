#include "catch.hpp"
#include "Math/SIMDMath.h"
#include "Math/Math.h"

using namespace ETL;
using namespace ETL::Math::SIMDMath;

//////////////////////////////////////////////////////////////////////////
// Vec4f
//////////////////////////////////////////////////////////////////////////
SCENARIO("vec4f SIMD math produces correct results", "[vec4f]")
{
	GIVEN("two vec4f object")
	{
		float vPre[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
		Vec4f v1 = Vec4fSet(1.0f, 2.0f, 3.0f, 4.0f);
		float v1x = Vec4fGetX(v1);
		float v1y = Vec4fGetY(v1);
		float v1z = Vec4fGetZ(v1);
		float v1w = Vec4fGetW(v1);
		Vec4f v2 = Vec4fSet(vPre);
		float vPost[4];
		Vec4fGet(vPost, v2);

		REQUIRE(v1x == 1.0f);
		REQUIRE(v1y == 2.0f);
		REQUIRE(v1z == 3.0f);
		REQUIRE(v1w == 4.0f);
		REQUIRE(vPre[0] == vPost[0]);
		REQUIRE(vPre[1] == vPost[1]);
		REQUIRE(vPre[2] == vPost[2]);
		REQUIRE(vPre[3] == vPost[3]);
	}

	GIVEN("a vec4f object")
	{
		float vPre[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
		Vec4f v = Vec4fSet(vPre);
		Vec4f lengthSq = Vec4fLengthSq(v);
		Vec4f length = Vec4fLength(v);
		Vec4f norm = Vec4fNormalize(v);
		Vec4f normLengthSq = Vec4fLengthSq(norm);

		REQUIRE(Vec4fGetX(lengthSq) == 30.0f);
		REQUIRE(Math::Scalar<float>::Equal(Vec4fGetX(length), Math::Sqrt(30.0f)));
		REQUIRE(Math::Scalar<float>::Equal(Vec4fGetX(normLengthSq), 1.0f));
	}

	GIVEN("three axis-aligned unit vectors")
	{
		Vec4f xAxis = Vec4fSet(1.0f, 0.0f, 0.0f, 0.0f);
		Vec4f yAxis = Vec4fSet(0.0f, 1.0f, 0.0f, 0.0f);
		Vec4f zAxis = Vec4fSet(0.0f, 0.0f, 1.0f, 0.0f);

		Vec4f xyRes = Vec4fCross(xAxis, yAxis);
		float xyResf[4];
		Vec4fGet(xyResf, xyRes);

		REQUIRE(xyResf[0] == 0.0f);
		REQUIRE(xyResf[1] == 0.0f);
		REQUIRE(xyResf[2] == 1.0f);
		REQUIRE(xyResf[3] == 0.0f);
	}
}