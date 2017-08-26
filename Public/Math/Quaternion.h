#pragma once

#include "Math/Math.h"
#include "Utility/Macros.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

// Disable the warning about negating unsigned values - that it doesn't do anything is expected behavior.
// #TODO: Do the same for LLVM and GCC
#if ETL_MSVC
#pragma warning(disable:4146)
#endif // ETL_MSVC

namespace ETL
{
	namespace Math
	{
		template<typename T> struct Quaternion;

		template<typename T>
		WideOStream& operator<< (WideOStream& out, const Quaternion<T>& rhs);

		template<typename T>
		MbOStream& operator<< (MbOStream& out, const Quaternion<T>& rhs);

		template<typename T>
		struct Quaternion
		{
			union
			{
				ETL_ALIGN(16) T Data[4];
				struct
				{
					T X;
					T Y;
					T Z;
					T W;
				};
			};

			static const Quaternion Identity;

			Quaternion(T x = Scalar<T>::Zero, T y = Scalar<T>::Zero, T z = Scalar<T>::Zero, T w = Scalar<T>::One) : X(x), Y(y), Z(z), W(w) { }
			Quaternion(const Vector3<T>& axis, T angle);
			Quaternion(const Vector4<T>& axisAngle);
			Quaternion(const T* arrData);
			Quaternion& operator=(const T* arrData);

			inline bool operator==(const Quaternion& rhs) const { return Scalar<T>::Equal(X, rhs.X) && Scalar<T>::Equal(Y, rhs.Y) && Scalar<T>::Equal(Z, rhs.Z) && Scalar<T>::Equal(W, rhs.W); }
			inline bool operator!=(const Quaternion& rhs) const { return Scalar<T>::NotEqual(X, rhs.X) || Scalar<T>::NotEqual(Y, rhs.Y) || Scalar<T>::NotEqual(Z, rhs.Z) || Scalar<T>::NotEqual(W, rhs.W); }

			inline Quaternion operator-() const { return Quaternion(-X, -Y, -Z, -W); }

			inline Quaternion operator+(const Quaternion& rhs) const { return Quaternion(X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W); }
			inline Quaternion operator-(const Quaternion& rhs) const { return Quaternion(X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W); }
			inline Quaternion operator*(T rhs) const { return Quaternion(X * rhs, Y * rhs, Z * rhs, W * rhs); }
			inline friend Quaternion operator*(T lhs, const Quaternion<T>& rhs) { return Quaternion<T>(lhs * rhs.X, lhs * rhs.Y, lhs * rhs.Z, lhs * rhs.W); }
			inline Quaternion operator/(T rhs) const { return Quaternion(X / rhs, Y / rhs, Z / rhs, W / rhs); }
			inline friend Quaternion operator/(T lhs, const Quaternion<T>& rhs) { return Quaternion<T>(lhs / rhs.X, lhs / rhs.Y, lhs / rhs.Z, lhs / rhs.W); }
			Quaternion operator*(const Quaternion& rhs) const;
			Quaternion operator/(const Quaternion& rhs) const;
			inline Quaternion& operator+=(const Quaternion& rhs) { X += rhs.X; Y += rhs.Y; Z += rhs.Z; W += rhs.W; return *this; }
			inline Quaternion& operator-=(const Quaternion& rhs) { X -= rhs.X; Y -= rhs.Y; Z -= rhs.Z; W -= rhs.W; return *this; }
			inline Quaternion& operator*=(T rhs) { X *= rhs; Y *= rhs; Z *= rhs; W *= rhs; return *this; }
			inline Quaternion& operator/=(T rhs) { X /= rhs; Y /= rhs; Z /= rhs; W /= rhs; return *this; }
			Quaternion& operator*=(const Quaternion& rhs);
			Quaternion& operator/=(const Quaternion& rhs);

			inline T Length() const { return Sqrt(X * X + Y * Y + Z * Z + W * W); }
			inline T LengthSq() const { return X * X + Y * Y + Z * Z + W * W; }
			Quaternion& Normalize();
			Quaternion Normalized() const;
			Quaternion& Conjugate();
			inline Quaternion Conjugated() const { return Quaternion(-X, -Y, -Z, W); }
			inline T Dot(const Quaternion& rhs) const { return X * rhs.X + Y * rhs.Y + Z * rhs.Z + W * rhs.W; }

			T AxisAngle(Vector3<T>& outAxis) const;
			Vector4<T> AxisAngle() const;

			operator WideString() const;
			friend WideOStream& operator<< <> (WideOStream& out, const Quaternion<T>& vec);

			operator MbString() const;
			friend MbOStream& operator<< <> (MbOStream& out, const Quaternion<T>& vec);
		};

#define ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(T, extension) typedef Quaternion<T> Quaternion ## extension; \
	extern template struct Quaternion<T>

		ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(float, f);
		ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(double, d);

#undef ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC
	}
}

#include "Quaternion.hpp"

#if ETL_MSVC
#pragma warning(default:4146)
#endif // ETL_MSVC