#pragma once

#include <xmmintrin.h> // SSE
#include <emmintrin.h> // SSE2
#include <pmmintrin.h> // SSE3
#include <tmmintrin.h> // SSSE3
#include <smmintrin.h> // SSE4.1
#include <nmmintrin.h> // SSE4.2

namespace ETL
{
namespace Math
{
namespace SIMDMath
{
	typedef __m128 Vec4f;
	typedef __m128d Vec2d;
	typedef __m128i Vec4i;

	//////////////////////////////////////////////////////////////////////////
	// Vec4f
	//////////////////////////////////////////////////////////////////////////
#define ETL_INTERNAL_VEC4F_MASK(x, y, z, w) (w << 6 | z << 4 | y << 2 | x)
#define ETL_INTERNAL_VEC4F_REPLICATE(v, a) _mm_shuffle_ps(v, v, ETL_INTERNAL_VEC4F_MASK(a, a, a, a))

	inline Vec4f Vec4fSet(float x, float y, float z, float w)
	{
		return _mm_set_ps(w, z, y, x);
	}

	inline Vec4f Vec4fSet(float x)
	{
		return _mm_set_ps1(x);
	}

	inline Vec4f Vec4fSetZero()
	{
		return _mm_setzero_ps();
	}

	inline Vec4f Vec4fSet(const float* pVec)
	{
		return _mm_load_ps(pVec);
	}

	inline float Vec4fGetX(Vec4f vec)
	{
		float retVal;
		_mm_store_ss(&retVal, vec);
		return retVal;
	}

	inline float Vec4fGetY(Vec4f vec)
	{
		float retVal;
		Vec4f shuffled = ETL_INTERNAL_VEC4F_REPLICATE(vec, 1);
		_mm_store_ss(&retVal, shuffled);
		return retVal;
	}

	inline float Vec4fGetZ(Vec4f vec)
	{
		float retVal;
		Vec4f shuffled = ETL_INTERNAL_VEC4F_REPLICATE(vec, 2);
		_mm_store_ss(&retVal, shuffled);
		return retVal;
	}

	inline float Vec4fGetW(Vec4f vec)
	{
		float retVal;
		Vec4f shuffled = ETL_INTERNAL_VEC4F_REPLICATE(vec, 3);
		_mm_store_ss(&retVal, shuffled);
		return retVal;
	}

	inline void Vec4fGet(float* pVec, Vec4f vec)
	{
		_mm_store_ps(pVec, vec);
	}

	inline Vec4f Vec4fAdd(Vec4f lhs, Vec4f rhs)
	{
		return _mm_add_ps(lhs, rhs);
	}

	inline Vec4f Vec4fSub(Vec4f lhs, Vec4f rhs)
	{
		return _mm_sub_ps(lhs, rhs);
	}

	inline Vec4f Vec4fMul(Vec4f lhs, Vec4f rhs)
	{
		return _mm_mul_ps(lhs, rhs);
	}

	inline Vec4f Vec4fDiv(Vec4f lhs, Vec4f rhs)
	{
		return _mm_div_ps(lhs, rhs);
	}

	inline Vec4f Vec4fSqrt(Vec4f vec)
	{
		return _mm_sqrt_ps(vec);
	}

	inline Vec4f Vec4fDot(Vec4f lhs, Vec4f rhs)
	{
		Vec4f multiplied = _mm_mul_ps(lhs, rhs);
		Vec4f zwxy = _mm_movehl_ps(multiplied, multiplied);
		Vec4f sum1 = _mm_add_ps(multiplied, zwxy);
		Vec4f sumYW = ETL_INTERNAL_VEC4F_REPLICATE(sum1, 1);
		Vec4f sum2 = _mm_add_ps(sum1, sumYW);
		return ETL_INTERNAL_VEC4F_REPLICATE(sum2, 0);
	}

	inline Vec4f Vec4fLengthSq(Vec4f vec)
	{
		return Vec4fDot(vec, vec);
	}

	inline Vec4f Vec4fLength(Vec4f vec)
	{
		return _mm_sqrt_ps(Vec4fLengthSq(vec));
	}

	inline Vec4f Vec4fNormalize(Vec4f vec)
	{
		return _mm_div_ps(vec, Vec4fLength(vec));
	}
}
}
}