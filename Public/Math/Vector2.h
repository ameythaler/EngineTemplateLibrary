#pragma once

#include "Math/Math.h"
#include "Utility/Macros.h"

namespace ETL
{
namespace Math
{
	template<typename T> struct Vector2;
	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
	typedef Vector2<int32> Vector2i;
	typedef Vector2<uint32> Vector2u;

	template<typename T>
	WideOStream& operator<< (WideOStream& out, const Vector2<T>& vec);

	template<typename T>
	MbOStream& operator<< (MbOStream& out, const Vector2<T>& vec);

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

		inline Vector2 operator-() const { return Vector2(-X, -Y); }

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
}
}

#include "Vector2.hpp"