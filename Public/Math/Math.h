#pragma once

#include "Utility/Types.h"
#include <math.h>
#include <algorithm>

namespace ETL
{
namespace Math
{
	template<typename T> struct Scalar;
	typedef Scalar<float> Scalarf;
	typedef Scalar<double> Scalard;
	typedef Scalar<int32> Scalari;
	typedef Scalar<uint32> Scalaru;

	inline float Sqrt(float val) { return sqrtf(val); }
	inline double Sqrt(double val) { return sqrt(val); }
	inline int32 Sqrt(int32 val) { return (int32)sqrtf((float)val); }
	inline uint32 Sqrt(uint32 val) { return (uint32)sqrtf((float)val); }

#define ETL_INTERNAL_MAX_FUNC(x) inline x Max(x a, x b) { return (a > b) ? a : b; }
#define ETL_INTERNAL_MIN_FUNC(x) inline x Min(x a, x b) { return (a < b) ? a : b; }

	ETL_INTERNAL_MAX_FUNC(int32);
	ETL_INTERNAL_MAX_FUNC(uint32);
	ETL_INTERNAL_MAX_FUNC(size_t);

	ETL_INTERNAL_MIN_FUNC(int32);
	ETL_INTERNAL_MIN_FUNC(uint32);
	ETL_INTERNAL_MIN_FUNC(size_t);

#undef ETL_INTERNAL_MAX_FUNC
#undef ETL_INTERNAL_MIN_FUNC

	template<typename T>
	struct Scalar
	{
		static const T Zero;
		static const T One;
	};

	template<>
	struct Scalar<float>
	{
		static const float Zero;
		static const float One;
	};

	template<>
	struct Scalar < double >
	{
		static const double Zero;
		static const double One;
	};

	template<>
	struct Scalar < int32 >
	{
		static const int32 Zero;
		static const int32 One;
	};

	template<>
	struct Scalar < uint32 >
	{
		static const uint32 Zero;
		static const uint32 One;
	};
}
}