#pragma once

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Utility/Macros.h"

// Disable the warning about negating unsigned values - that it doesn't do anything is expected behavior.
// #TODO: Do the same for LLVM and GCC
#if ETL_MSVC
#pragma warning(disable:4146) 
#endif // ETL_MSVC

namespace ETL
{
	namespace Math
	{
		template<typename T> struct Vector4;

		template<typename T>
		WideOStream& operator<< (WideOStream& out, const Vector4<T>& vec);

		template<typename T>
		MbOStream& operator<< (MbOStream& out, const Vector4<T>& vec);

		// These two specialization keep the uint8 and int8 components from being interpreted as characters.
		template<>
		MbOStream& operator<< (MbOStream& out, const Vector4<uint8>& vec);

		template<>
		MbOStream& operator<< (MbOStream& out, const Vector4<int8>& vec);

		template<typename T>
		struct ETL_ALIGN(16) Vector4
		{
			union
			{
				T Data[4];
				struct
				{
					T X;
					T Y;
					T Z;
					T W;
				};
				Vector2<T> XY;
				Vector3<T> XYZ;
			};

			static const Vector4 Zero;
			static const Vector4 One;
			static const Vector4 XAxis;
			static const Vector4 YAxis;
			static const Vector4 ZAxis;

			Vector4(T x = Scalar<T>::Zero, T y = Scalar<T>::Zero, T z = Scalar<T>::Zero, T w = Scalar<T>::Zero) : X(x), Y(y), Z(z), W(w) { }
			Vector4(const Vector3<T>& xyz, T w = Scalar<T>::One) : XYZ(xyz), W(w) { }
			Vector4(const T* arrData);
			Vector4& operator=(const Vector4& rhs); // #TODO I don't think I need this
			Vector4& operator=(const T* arrData);

			inline bool operator==(const Vector4& rhs) const { return Scalar<T>::Equal(X, rhs.X) && Scalar<T>::Equal(Y, rhs.Y) && Scalar<T>::Equal(Z, rhs.Z) && Scalar<T>::Equal(W, rhs.W); }
			inline bool operator!=(const Vector4& rhs) const { return Scalar<T>::NotEqual(X, rhs.X) || Scalar<T>::NotEqual(Y, rhs.Y) || Scalar<T>::NotEqual(Z, rhs.Z) || Scalar<T>::NotEqual(W, rhs.W); }

			inline Vector4 operator-() const { return Vector4(-X, -Y, -Z, -W); }

			inline Vector4 operator+(const Vector4& rhs) const { return Vector4(X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W); }
			inline Vector4 operator-(const Vector4& rhs) const { return Vector4(X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W); }
			inline Vector4 operator*(T rhs) const { return Vector4(X * rhs, Y * rhs, Z * rhs, W * rhs); }
			inline friend Vector4 operator*(T lhs, const Vector4<T>& rhs) { return Vector4<T>(lhs * rhs.X, lhs * rhs.Y, lhs * rhs.Z, lhs * rhs.W); }
			inline Vector4 operator/(T rhs) const { return Vector4(X / rhs, Y / rhs, Z / rhs, W / rhs); }
			inline friend Vector4 operator/(T lhs, const Vector4<T>& rhs) { return Vector4<T>(lhs / rhs.X, lhs / rhs.Y, lhs / rhs.Z, lhs / rhs.W); }
			inline Vector4 operator*(const Vector4& rhs) const { return Vector4(X * rhs.X, Y * rhs.Y, Z * rhs.Z, W * rhs.W); }
			inline Vector4 operator/(const Vector4& rhs) const { return Vector4(X / rhs.X, Y / rhs.Y, Z / rhs.Z, W / rhs.W); }
			inline Vector4& operator+=(const Vector4& rhs) { X += rhs.X; Y += rhs.Y; Z += rhs.Z; W += rhs.W; return *this; }
			inline Vector4& operator-=(const Vector4& rhs) { X -= rhs.X; Y -= rhs.Y; Z -= rhs.Z; W -= rhs.W; return *this; }
			inline Vector4& operator*=(T rhs) { X *= rhs; Y *= rhs; Z *= rhs; W *= rhs; return *this; }
			inline Vector4& operator/=(T rhs) { X /= rhs; Y /= rhs; Z /= rhs; W /= rhs; return *this; }
			inline Vector4& operator*=(const Vector4& rhs) { X *= rhs.X; Y *= rhs.Y; Z *= rhs.Z; W *= rhs.W; return *this; }
			inline Vector4& operator/=(const Vector4& rhs) { X /= rhs.X; Y /= rhs.Y; Z /= rhs.Z; W /= rhs.W; return *this; }

			inline T Length() const { return Sqrt(X * X + Y * Y + Z * Z + W * W); }
			inline T LengthSq() const { return X * X + Y * Y + Z * Z + W * W; }
			Vector4& Normalize();
			Vector4 Normalized() const;
			inline T Dot(const Vector4& rhs) const { return X * rhs.X + Y * rhs.Y + Z * rhs.Z + W * rhs.W; }
			inline Vector4 Cross(const Vector4& rhs) const;
			Vector4 Project(const Vector4& axis) const;

			operator WideString() const;
			friend WideOStream& operator<< <> (WideOStream& out, const Vector4<T>& vec);

			operator MbString() const;
			friend MbOStream& operator<< <> (MbOStream& out, const Vector4<T>& vec);
		};

#define ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(T, extension) typedef Vector4<T> Vector4 ## extension; \
	extern template struct Vector4<T>

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

#include "Vector4.hpp"

#if ETL_MSVC
#pragma warning(default:4146)
#endif // ETL_MSVC