#pragma once

#include "Math/Math.h"
#include "Utility/Macros.h"

namespace ETL
{
namespace Math
{
	template<typename T> struct Vector2;

	template<typename T>
	WideOStream& operator<< (WideOStream& out, const Vector2<T>& vec);

	template<typename T>
	MbOStream& operator<< (MbOStream& out, const Vector2<T>& vec);

	// These two specialization keep the uint8 and int8 components from being interpreted as characters.
	template<>
	MbOStream& operator<< (MbOStream& out, const Vector2<uint8>& vec);

	template<>
	MbOStream& operator<< (MbOStream& out, const Vector2<int8>& vec);

	template<typename T>
	struct Vector2
	{
		union
		{
			ETL_ALIGN(16) T Data[2];
			struct
			{
				T X;
				T Y;
			};
		};

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 XAxis;
		static const Vector2 YAxis;

		Vector2(T x = Scalar<T>::Zero, T y = Scalar<T>::Zero) : X(x), Y(y) { }
		Vector2(const T* arrData);
		Vector2& operator=(const Vector2& rhs);
		Vector2& operator=(const T* arrData);

		inline bool operator==(const Vector2& rhs) const { return Scalar<T>::Equal(X, rhs.X) && Scalar<T>::Equal(Y, rhs.Y); }
		inline bool operator!=(const Vector2& rhs) const { return Scalar<T>::NotEqual(X, rhs.X) || Scalar<T>::NotEqual(Y, rhs.Y); }

		// Disable the warning about negating unsigned values - that it doesn't do anything is expected behavior.
		// TODO: Do the same for LLVM and GCC
#if ETL_MSVC
#pragma warning(disable:4146) 
#endif // ETL_MSVC
		inline Vector2 operator-() const { return Vector2(-X, -Y); }
#if ETL_MSVC
#pragma warning(default:4146)
#endif // ETL_MSVC

		inline Vector2 operator+(const Vector2& rhs) const { return Vector2(X + rhs.X, Y + rhs.Y); }
		inline Vector2 operator-(const Vector2& rhs) const { return Vector2(X - rhs.X, Y - rhs.Y); }
		inline Vector2 operator*(T rhs) const { return Vector2(X * rhs, Y * rhs); }
		inline friend Vector2 operator*(T lhs, const Vector2<T>& rhs) { return Vector2<T>(lhs * rhs.X, lhs * rhs.Y); }
		inline Vector2 operator/(T rhs) const { return Vector2(X / rhs, Y / rhs); }
		inline friend Vector2 operator/(T lhs, const Vector2<T>& rhs) { return Vector2<T>(lhs / rhs.X, lhs / rhs.Y); }
		inline Vector2 operator*(const Vector2& rhs) const { return Vector2(X * rhs.X, Y * rhs.Y); }
		inline Vector2 operator/(const Vector2& rhs) const { return Vector2(X / rhs.X, Y / rhs.Y); }
		inline Vector2& operator+=(const Vector2& rhs) { X += rhs.X; Y += rhs.Y; return *this; }
		inline Vector2& operator-=(const Vector2& rhs) { X -= rhs.X; Y -= rhs.Y; return *this; }
		inline Vector2& operator*=(T rhs) { X *= rhs; Y *= rhs; return *this; }
		inline Vector2& operator/=(T rhs) { X /= rhs; Y /= rhs; return *this; }
		inline Vector2& operator*=(const Vector2& rhs) { X *= rhs.X; Y *= rhs.Y; return *this; }
		inline Vector2& operator/=(const Vector2& rhs) { X /= rhs.X; Y /= rhs.Y; return *this; }

		inline T Length() const { return Sqrt(X * X + Y * Y); }
		inline T LengthSq() const { return X * X + Y * Y; }
		Vector2& Normalize();
		Vector2 Normalized() const;
		inline T Dot(const Vector2& rhs) const { return X * rhs.X + Y * rhs.Y; }
		inline Vector2 Cross() const { return Vector2(Y, X); }
		Vector2 Project(const Vector2& axis) const;

		operator WideString() const;
		friend WideOStream& operator<< <> (WideOStream& out, const Vector2<T>& vec);

		operator MbString() const;
		friend MbOStream& operator<< <> (MbOStream& out, const Vector2<T>& vec);
	};

#define ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(T, extension) typedef Vector2<T> Vector2 ## extension; \
	extern template struct Vector2<T>

	ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(float, f);
	ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(double, d);
	ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(int32, i32);
	ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(uint32, u32);
	ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(int64, i64);
	ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(uint64, u64);
	ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(int16, i16);
	ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(uint16, u16);
	ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(int8, i8);
	ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(uint8, u8);

#undef ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC
}
}

#include "Vector2.hpp"