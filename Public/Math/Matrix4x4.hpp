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
			, M10(m10), M11(m11), M12(m12), M13(m13)
			, M20(m20), M21(m21), M22(m22), M23(m23)
			, M30(m30), M31(m31), M32(m32), M33(m33)
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

		template<typename T>
		Matrix4x4<T>& Matrix4x4<T>::operator*=(const Matrix4x4<T>& rhs)
		{
			Vector4<T> x = X;
			Vector4<T> y = Y;
			Vector4<T> z = Z;
			Vector4<T> w = W;
			X = ETL_INTERNAL_MUL_ROW(x, rhs);
			Y = ETL_INTERNAL_MUL_ROW(y, rhs);
			Z = ETL_INTERNAL_MUL_ROW(z, rhs);
			W = ETL_INTERNAL_MUL_ROW(w, rhs);
			return *this;
		}

#undef ETL_INTERNAL_MUL_ROW
#undef ETL_INTERNAL_DOT

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::Transposed() const
		{
			return Matrix4x4<T>(M00, M10, M20, M30
				, M01, M11, M21, M31
				, M02, M12, M22, M32
				, M03, M13, M23, M33);
		}

		template<typename T>
		Matrix4x4<T>& Matrix4x4<T>::Transpose()
		{
			std::swap(M01, M10);
			std::swap(M02, M20);
			std::swap(M03, M30);
			std::swap(M12, M21);
			std::swap(M13, M31);
			std::swap(M23, M32);
			return *this;
		}

		template<typename T>
		Vector3<T> Matrix4x4<T>::Transform(const Vector3<T>& rhs) const
		{
			Vector4<T> v(rhs, 1.0f);
			Vector4<T> retVal(X.Dot(v), Y.Dot(v), Z.Dot(v), W.Dot(v));
			return retVal.XYZ / retVal.W;
		}

		template<typename T>
		Vector4<T> Matrix4x4<T>::Transform(const Vector4<T>& rhs) const
		{
			return Vector4<T>(X.Dot(rhs), Y.Dot(rhs), Z.Dot(rhs), W.Dot(rhs));
		}

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