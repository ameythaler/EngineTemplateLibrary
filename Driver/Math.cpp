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