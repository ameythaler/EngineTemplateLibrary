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
	typedef Scalar<int32> Scalari32;
	typedef Scalar<uint32> Scalaru32;
	typedef Scalar<int64> Scalari64;
	typedef Scalar<uint64> Scalaru64;
	typedef Scalar<int16> Scalari16;
	typedef Scalar<uint16> Scalaru16;
	typedef Scalar<int8> Scalari8;
	typedef Scalar<uint8> Scalaru8;

#define ETL_INTERNAL_TRIG(x, y) inline float x(float val) { return y ## f(val); } \
	inline double x(double val) { return y(val); }

	ETL_INTERNAL_TRIG(Sin, sin)
	ETL_INTERNAL_TRIG(Cos, cos)
	ETL_INTERNAL_TRIG(Tan, tan)
	ETL_INTERNAL_TRIG(ASin, asin)
	ETL_INTERNAL_TRIG(ACos, acos)
	ETL_INTERNAL_TRIG(ATan, atan)

#undef ETL_INTERNAL_TRIG

	inline float Abs(float val) { return abs(val); }
	inline double Abs(double val) { return abs(val); }

#define ETL_INTERNAL_INT_ABS(x) inline x Abs(x val) { return (x)abs(val); }
#define ETL_INTERNAL_INT_ABS_UNSIGNED(x) inline x Abs(x val) { return val; } // unsigned values are already positive - this is necessary only for templated constructs

	ETL_INTERNAL_INT_ABS(int32)
	ETL_INTERNAL_INT_ABS_UNSIGNED(uint32)
	ETL_INTERNAL_INT_ABS(int64)
	ETL_INTERNAL_INT_ABS_UNSIGNED(uint64)
	ETL_INTERNAL_INT_ABS(int16)
	ETL_INTERNAL_INT_ABS_UNSIGNED(uint16)
	ETL_INTERNAL_INT_ABS(int8)
	ETL_INTERNAL_INT_ABS_UNSIGNED(uint8)

#undef ETL_INTERNAL_INT_ABS
#undef ETL_INTERNAL_INT_ABS_UNSIGNED

	inline float Sqrt(float val) { return sqrtf(val); }
	inline double Sqrt(double val) { return sqrt(val); }

#define ETL_INTERNAL_INT_SQRT(x) inline x Sqrt(x val) { return (x)sqrtf((float)val); }

	ETL_INTERNAL_INT_SQRT(int32)
	ETL_INTERNAL_INT_SQRT(uint32)
	ETL_INTERNAL_INT_SQRT(int64)
	ETL_INTERNAL_INT_SQRT(uint64)
	ETL_INTERNAL_INT_SQRT(int16)
	ETL_INTERNAL_INT_SQRT(uint16)
	ETL_INTERNAL_INT_SQRT(int8)
	ETL_INTERNAL_INT_SQRT(uint8)

#undef ETL_INTERNAL_INT_SQRT

#define ETL_INTERNAL_MAX_FUNC(x) inline x Max(x a, x b) { return (a > b) ? a : b; }
#define ETL_INTERNAL_MIN_FUNC(x) inline x Min(x a, x b) { return (a < b) ? a : b; }

	ETL_INTERNAL_MAX_FUNC(int32)
	ETL_INTERNAL_MAX_FUNC(uint32)
	ETL_INTERNAL_MAX_FUNC(int64)
	ETL_INTERNAL_MAX_FUNC(uint64)
	ETL_INTERNAL_MAX_FUNC(int16)
	ETL_INTERNAL_MAX_FUNC(uint16)
	ETL_INTERNAL_MAX_FUNC(int8)
	ETL_INTERNAL_MAX_FUNC(uint8)
	ETL_INTERNAL_MAX_FUNC(float)
	ETL_INTERNAL_MAX_FUNC(double)

	ETL_INTERNAL_MIN_FUNC(int32)
	ETL_INTERNAL_MIN_FUNC(uint32)
	ETL_INTERNAL_MIN_FUNC(int64)
	ETL_INTERNAL_MIN_FUNC(uint64)
	ETL_INTERNAL_MIN_FUNC(int16)
	ETL_INTERNAL_MIN_FUNC(uint16)
	ETL_INTERNAL_MIN_FUNC(int8)
	ETL_INTERNAL_MIN_FUNC(uint8)
	ETL_INTERNAL_MIN_FUNC(float)
	ETL_INTERNAL_MIN_FUNC(double)

#undef ETL_INTERNAL_MAX_FUNC
#undef ETL_INTERNAL_MIN_FUNC

	template<typename T>
	struct Scalar
	{
		static const T Zero;
		static const T One;
		static const T Two;
		static const T Four;
		static const T Epsilon;
		static const T Pi;
		static const T Pi2;
		static const T Pi4;
		static const T PiOver2;
		static const T PiOver4;
		static bool Equal(T lhs, T rhs);
		static bool NotEqual(T lhs, T rhs);
	};

#define ETL_INTERNAL_EXPLICIT_DEC_SCALAR(T) template<> \
	struct Scalar<T> \
	{ \
		static const T Zero; \
		static const T One; \
		static const T Two; \
		static const T Four; \
		static const T Epsilon; \
		static const T Pi; \
		static const T Pi2; \
		static const T Pi4; \
		static const T PiOver2; \
		static const T PiOver4; \
		static bool Equal(T lhs, T rhs); \
		static bool NotEqual(T lhs, T rhs); \
	}; \
	extern template struct Scalar<T>

	ETL_INTERNAL_EXPLICIT_DEC_SCALAR(float);
	ETL_INTERNAL_EXPLICIT_DEC_SCALAR(double);
	ETL_INTERNAL_EXPLICIT_DEC_SCALAR(int32);
	ETL_INTERNAL_EXPLICIT_DEC_SCALAR(uint32);
	ETL_INTERNAL_EXPLICIT_DEC_SCALAR(int64);
	ETL_INTERNAL_EXPLICIT_DEC_SCALAR(uint64);
	ETL_INTERNAL_EXPLICIT_DEC_SCALAR(int16);
	ETL_INTERNAL_EXPLICIT_DEC_SCALAR(uint16);
	ETL_INTERNAL_EXPLICIT_DEC_SCALAR(int8);
	ETL_INTERNAL_EXPLICIT_DEC_SCALAR(uint8);

#undef ETL_INTERNAL_EXPLICIT_DEC_SCALAR

	inline float ToRadians(float degrees) { return degrees * Scalarf::Pi / 180.0f; }
	inline double ToRadians(double degrees) { return degrees * Scalard::Pi / 180.0; }
	inline float ToDegrees(float radians) { return radians * 180.0f / Scalarf::Pi; }
	inline double ToDegrees(double radians) { return radians * 180.0 / Scalard::Pi; }
}
}