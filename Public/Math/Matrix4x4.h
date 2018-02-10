#pragma once

#include "Math/Math.h"
#include "Math/Vector4.h"
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
					T M00, M01, M02, M03;
					T M10, M11, M12, M13;
					T M20, M21, M22, M23;
					T M30, M31, M32, M33;
				};
			};

			static const Matrix4x4 Zero;
			static const Matrix4x4 One;
			static const Matrix4x4 Identity;

			Matrix4x4(T m00 = Scalar<T>::One, T m01 = Scalar<T>::Zero, T m02 = Scalar<T>::Zero, T m03 = Scalar<T>::Zero
				, T m10 = Scalar<T>::Zero, T m11 = Scalar<T>::One, T m12 = Scalar<T>::Zero, T m13 = Scalar<T>::Zero
				, T m20 = Scalar<T>::Zero, T m21 = Scalar<T>::Zero, T m22 = Scalar<T>::One, T m23 = Scalar<T>::Zero
				, T m30 = Scalar<T>::Zero, T m31 = Scalar<T>::Zero, T m32 = Scalar<T>::Zero, T m33 = Scalar<T>::One);
			Matrix4x4(const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w);
			Matrix4x4(const T* arrData);
			Matrix4x4& operator=(const T* arrData);

			Matrix4x4 operator+(const Matrix4x4& rhs) const;
			Matrix4x4 operator-(const Matrix4x4& rhs) const;

			operator WideString() const;
			friend WideOStream& operator<< <> (WideOStream& out, const Matrix4x4<T>& mat);

			operator MbString() const;
			friend MbOStream& operator<< <> (MbOStream& out, const Matrix4x4<T>& mat);
		};

#define ETL_INTERNAL_EXPLICIT_SPEC_INST_DEC(T, extension) typedef Matrix4x4<T> Matrix4x4 ## extension; \
	extern template struct Matrix4x4<T>

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

#include "Matrix4x4.hpp"

#if ETL_MSVC
#pragma warning(default:4146)
#endif // ETL_MSVC