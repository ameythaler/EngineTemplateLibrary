#pragma once

#include "Math/Math.h"
#include "Math/Vector4.h"
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
		template<typename T> struct Matrix4x4;

		template<typename T>
		WideOStream& operator<< (WideOStream& out, const Matrix4x4<T>& mat);

		template<typename T>
		MbOStream& operator<< (MbOStream& out, const Matrix4x4<T>& mat);

		// These two specialization keep the uint8 and int8 components from being interpreted as characters.
		template<>
		MbOStream& operator<< (MbOStream& out, const Matrix4x4<uint8>& mat);

		template<>
		MbOStream& operator<< (MbOStream& out, const Matrix4x4<int8>& mat);

		template<typename T>
		struct ETL_ALIGN(16) Matrix4x4
		{
			union
			{
				T Data[16];
				struct  
				{
					Vector4<T> X;
					Vector4<T> Y;
					Vector4<T> Z;
					Vector4<T> W;
				};
				struct  
				{
#if ETL_D3D_MATRIX
					// Row Major
					T M00, M01, M02, M03;
					T M10, M11, M12, M13;
					T M20, M21, M22, M23;
					T M30, M31, M32, M33;
#else // ETL_D3D_MATRIX
					// Column Major
					T M00, M10, M20, M30;
					T M01, M11, M21, M31;
					T M02, M12, M22, M32;
					T M03, M13, M23, M33;
#endif // ETL_D3D_MATRIX
				};
			};

			static const Matrix4x4 Zero;
			static const Matrix4x4 One;
			static const Matrix4x4 Identity;

#if ETL_D3D_MATRIX
			Matrix4x4(T m00, T m01, T m02, T m03
					, T m10, T m11, T m12, T m13
					, T m20, T m21, T m22, T m23
					, T m30, T m31, T m32, T m33);
#else // ETL_D3D_MATRIX
			Matrix4x4(T m00, T m10, T m20, T m30
					, T m01, T m11, T m21, T m31
					, T m02, T m12, T m22, T m32
					, T m03, T m13, T m23, T m33);
#endif // ETL_D3D_MATRIX
			Matrix4x4(T xDiag = Scalar<T>::One, T yDiag = Scalar<T>::One, T zDiag = Scalar<T>::One, T wDiag = Scalar<T>::One, T fill = Scalar<T>::Zero);
			Matrix4x4(const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w);
			inline Matrix4x4(const T* arrData) { memcpy(Data, arrData, sizeof(T) * 16); }
			inline Matrix4x4& operator=(const Matrix4x4& rhs) { memcpy(Data, rhs.Data, sizeof(T) * 16); return *this; }
			inline Matrix4x4& operator=(const T* arrData) { memcpy(Data, arrData, sizeof(T) * 16); return *this; }

			inline bool operator==(const Matrix4x4& rhs) const { return X == rhs.X && Y == rhs.Y && Z == rhs.Z && W == rhs.W; }
			inline bool operator!=(const Matrix4x4& rhs) const { return X != rhs.X || Y != rhs.Y || Z != rhs.Z || W != rhs.Z; }

			inline Matrix4x4 operator+(const Matrix4x4& rhs) const { return Matrix4x4(X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W); }
			inline Matrix4x4 operator-(const Matrix4x4& rhs) const { return Matrix4x4(X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W); }
			inline Matrix4x4 operator*(T rhs) const { return Matrix4x4(X * rhs, Y * rhs, Z * rhs, W * rhs); }
			Matrix4x4 operator*(const Matrix4x4& rhs) const;
			inline Matrix4x4 operator/(T rhs) const { return Matrix4x4(X / rhs, Y / rhs, Z / rhs, W / rhs); }
			inline Matrix4x4& operator+=(const Matrix4x4& rhs) { X += rhs.X; Y += rhs.Y; Z += rhs.Z; W += rhs.W; return *this; }
			inline Matrix4x4& operator-=(const Matrix4x4& rhs) { X -= rhs.X; Y -= rhs.Y; Z -= rhs.Z; W -= rhs.W; return *this; }
			inline Matrix4x4& operator*=(T rhs) { X *= rhs; Y *= rhs; Z *= rhs; W *= rhs; return *this; }
			Matrix4x4& operator*=(const Matrix4x4& rhs);
			inline Matrix4x4& operator/=(T rhs) { X /= rhs; Y /= rhs; Z /= rhs; W /= rhs; return *this; }

			inline Matrix4x4 MultiplyComponents(const Matrix4x4& rhs) const { return Matrix4x4(X * rhs.X, Y * rhs.Y, Z * rhs.Z, W * rhs.W); }
			inline Matrix4x4 DivideComponents(const Matrix4x4& rhs) const { return Matrix4x4(X / rhs.X, Y / rhs.Y, Z / rhs.Z, W / rhs.W); }

			Matrix4x4 Transposed() const;
			Matrix4x4& Transpose();

			Vector3<T> Transform(const Vector3<T>& rhs) const;
			Vector4<T> Transform(const Vector4<T>& rhs) const;

			static Matrix4x4 MakeTranslation(const Vector3<T>& translation);
			static Matrix4x4 MakeTranslation(T x, T y, T z);
			static Matrix4x4 MakeRotationX(T radians);
			static Matrix4x4 MakeRotationY(T radians);
			static Matrix4x4 MakeRotationZ(T radians);
			static Matrix4x4 MakeScale(T scale);
			static Matrix4x4 MakeScale(const Vector3<T>& scale);
			static Matrix4x4 MakeScale(T x, T y, T z);

			operator WideString() const;
			friend WideOStream& operator<< <> (WideOStream& out, const Matrix4x4<T>& mat);

			operator MbString() const;
			friend MbOStream& operator<< <> (MbOStream& out, const Matrix4x4<T>& mat);
		};

#define ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(T, extension) typedef Matrix4x4<T> Matrix4x4 ## extension; \
	extern template struct Matrix4x4<T>

		ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(float, f);
		ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(double, d);

#undef ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC
	}
}

#include "Matrix4x4.hpp"

#if ETL_MSVC
#pragma warning(default:4146)
#endif // ETL_MSVC