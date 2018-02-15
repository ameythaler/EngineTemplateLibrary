namespace ETL
{
	namespace Math
	{
		template<typename T>
		const Matrix4x4<T> Matrix4x4<T>::Zero = Matrix4x4<T>(Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero
			, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero
			, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero
			, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero);

		template<typename T>
		const Matrix4x4<T> Matrix4x4<T>::One = Matrix4x4<T>(Scalar<T>::One, Scalar<T>::One, Scalar<T>::One, Scalar<T>::One
			, Scalar<T>::One, Scalar<T>::One, Scalar<T>::One, Scalar<T>::One
			, Scalar<T>::One, Scalar<T>::One, Scalar<T>::One, Scalar<T>::One
			, Scalar<T>::One, Scalar<T>::One, Scalar<T>::One, Scalar<T>::One);

		template<typename T>
		const Matrix4x4<T> Matrix4x4<T>::Identity = Matrix4x4<T>(Scalar<T>::One, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero
			, Scalar<T>::Zero, Scalar<T>::One, Scalar<T>::Zero, Scalar<T>::Zero
			, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::One, Scalar<T>::Zero
			, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::One);

		template<typename T>
		Matrix4x4<T>::Matrix4x4(T m00, T m01, T m02, T m03
			, T m10, T m11, T m12, T m13
			, T m20, T m21, T m22, T m23
			, T m30, T m31, T m32, T m33)
			: M00(m00), M01(m01), M02(m02), M03(m03)
			, M10(m00), M11(m01), M12(m02), M13(m03)
			, M20(m00), M21(m01), M22(m02), M23(m03)
			, M30(m00), M31(m01), M32(m02), M33(m03)
		{
		}

		template<typename T>
		Matrix4x4<T>::Matrix4x4(const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}

#define ETL_INTERNAL_DOT(r, c, rhs) r.X * rhs.M0 ## c + r.Y * rhs.M1 ## c + r.Z * rhs.M2 ## c + r.W * rhs.M3 ## c
#define ETL_INTERNAL_MUL_ROW(v, rhs) ETL_INTERNAL_DOT(v, 0, rhs), ETL_INTERNAL_DOT(v, 1, rhs), ETL_INTERNAL_DOT(v, 2, rhs), ETL_INTERNAL_DOT(v, 3, rhs)

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& rhs) const
		{
			return Matrix4x4<T>(ETL_INTERNAL_MUL_ROW(X, rhs), ETL_INTERNAL_MUL_ROW(Y, rhs), ETL_INTERNAL_MUL_ROW(Z, rhs), ETL_INTERNAL_MUL_ROW(W, rhs));
		}

#undef ETL_INTERNAL_MUL_ROW
#undef ETL_INTERNAL_DOT

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeTranslation(const Vector3<T>& translation)
		{
			Matrix4x4<T> retVal;
			retVal.W.XYZ = translation;
			return retVal;
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeRotationX(T radians)
		{
			Matrix4x4<T> retVal;
			retVal.M11 = Cos(radians);
			retVal.M12 = Sin(radians);
			retVal.M21 = -Sin(radians);
			retVal.M22 = Cos(radians);
			return retVal;
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeRotationY(T radians)
		{
			Matrix4x4<T> retVal;
			retVal.M00 = Cos(radians);
			retVal.M02 = -Sin(radians);
			retVal.M20 = Sin(radians);
			retVal.M22 = Cos(radians);
			return retVal;
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeRotationZ(T radians)
		{
			Matrix4x4<T> retVal;
			retVal.M00 = Cos(radians);
			retVal.M01 = Sin(radians);
			retVal.M10 = -Sin(radians);
			retVal.M11 = Cos(radians);
			return retVal;
		}

		template<typename T>
		Matrix4x4<T>::operator WideString() const
		{
			WideStringStream stream;
			stream << *this;
			return stream.str();
		}

		template<typename T>
		WideOStream& operator<<(WideOStream& out, const Matrix4x4<T>& mat)
		{
			out << L"[" << mat.X << L", " << mat.Y << L", " << mat.Z << L", " << mat.W << L"]";
			return out;
		}

		template<typename T>
		Matrix4x4<T>::operator MbString() const
		{
			MbStringStream stream;
			stream << *this;
			return stream.str();
		}

		template<typename T>
		MbOStream& operator<<(MbOStream& out, const Matrix4x4<T>& mat)
		{
			out << "[" << mat.X << ", " << mat.Y << ", " << mat.Z << ", " << mat.W << "]";
			return out;
		}
	}
}