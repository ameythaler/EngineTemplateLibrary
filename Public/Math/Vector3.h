#pragma once

#include "Math/Math.h"
#include "Utility/Macros.h"
#include "Math/Vector2.h"

// Disable the warning about negating unsigned values - that it doesn't do anything is expected behavior.
// TODO: Do the same for LLVM and GCC
#if ETL_MSVC
#pragma warning(disable:4146) 
#endif // ETL_MSVC

namespace ETL
{
	namespace Math
	{
		template<typename T> struct Vector3;

		template<typename T>
		WideOStream& operator<< (WideOStream& out, const Vector3<T>& vec);

		template<typename T>
		MbOStream& operator<< (MbOStream& out, const Vector3<T>& vec);

		// These two specialization keep the uint8 and int8 components from being interpreted as characters.
		template<>
		MbOStream& operator<< (MbOStream& out, const Vector3<uint8>& vec);

		template<>
		MbOStream& operator<< (MbOStream& out, const Vector3<int8>& vec);

		template<typename T>
		struct Vector3
		{
			union
			{
				ETL_ALIGN(16) T Data[3];
				struct
				{
					T X;
					T Y;
					T Z;
				};
			};

			static const Vector3 Zero;
			static const Vector3 One;
			static const Vector3 XAxis;
			static const Vector3 YAxis;
			static const Vector3 ZAxis;

			Vector3(T x = Scalar<T>::Zero, T y = Scalar<T>::Zero, T z = Scalar<T>::Zero) : X(x), Y(y), Z(z) { }
			Vector3(const T* arrData);
			Vector3& operator=(const Vector3& rhs);
			Vector3& operator=(const T* arrData);

			inline bool operator==(const Vector3& rhs) const { return Scalar<T>::Equal(X, rhs.X) && Scalar<T>::Equal(Y, rhs.Y) && Scalar<T>::Equal(Z, rhs.Z); }
			inline bool operator!=(const Vector3& rhs) const { return Scalar<T>::NotEqual(X, rhs.X) || Scalar<T>::NotEqual(Y, rhs.Y) || Scalar<T>::NotEqual(Z, rhs.Z); }

			inline Vector3 operator-() const { return Vector3(-X, -Y, -Z); }

			inline Vector3 operator+(const Vector3& rhs) const { return Vector3(X + rhs.X, Y + rhs.Y, Z + rhs.Z); }
			inline Vector3 operator-(const Vector3& rhs) const { return Vector3(X - rhs.X, Y - rhs.Y, Z - rhs.Z); }
			inline Vector3 operator*(T rhs) const { return Vector3(X * rhs, Y * rhs, Z * rhs); }
			inline friend Vector3 operator*(T lhs, const Vector3<T>& rhs) { return Vector3<T>(lhs * rhs.X, lhs * rhs.Y, lhs * rhs.Z); }
			inline Vector3 operator/(T rhs) const { return Vector3(X / rhs, Y / rhs, Z / rhs); }
			inline friend Vector3 operator/(T lhs, const Vector3<T>& rhs) { return Vector3<T>(lhs / rhs.X, lhs / rhs.Y, lhs / rhs.Z); }
			inline Vector3 operator*(const Vector3& rhs) const { return Vector3(X * rhs.X, Y * rhs.Y, Z * rhs.Z); }
			inline Vector3 operator/(const Vector3& rhs) const { return Vector3(X / rhs.X, Y / rhs.Y, Z / rhs.Z); }
			inline Vector3& operator+=(const Vector3& rhs) { X += rhs.X; Y += rhs.Y; Z += rhs.Z; return *this; }
			inline Vector3& operator-=(const Vector3& rhs) { X -= rhs.X; Y -= rhs.Y; Z -= rhs.Z; return *this; }
			inline Vector3& operator*=(T rhs) { X *= rhs; Y *= rhs; Z *= rhs; return *this; }
			inline Vector3& operator/=(T rhs) { X /= rhs; Y /= rhs; Z /= rhs; return *this; }
			inline Vector3& operator*=(const Vector3& rhs) { X *= rhs.X; Y *= rhs.Y; Z *= rhs.Z; return *this; }
			inline Vector3& operator/=(const Vector3& rhs) { X /= rhs.X; Y /= rhs.Y; Z /= rhs.Z; return *this; }

			inline T Length() const { return Sqrt(X * X + Y * Y + Z * Z); }
			inline T LengthSq() const { return X * X + Y * Y + Z * Z; }
			Vector3& Normalize();
			Vector3 Normalized() const;
			inline T Dot(const Vector3& rhs) const { return X * rhs.X + Y * rhs.Y + Z * rhs.Z; }
			inline Vector3 Cross(const Vector3& rhs) const;
			Vector3 Project(const Vector3& axis) const;

			operator WideString() const;
			friend WideOStream& operator<< <> (WideOStream& out, const Vector3<T>& vec);

			operator MbString() const;
			friend MbOStream& operator<< <> (MbOStream& out, const Vector3<T>& vec);
		};

#define ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(T, extension) typedef Vector3<T> Vector3 ## extension; \
	extern template struct Vector3<T>

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

#include "Vector3.hpp"

#if ETL_MSVC
#pragma warning(default:4146)
#endif // ETL_MSVC