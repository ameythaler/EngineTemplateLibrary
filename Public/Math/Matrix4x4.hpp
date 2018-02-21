namespace ETL
{
	namespace Math
	{
		template<typename T>
		const Matrix4x4<T> Matrix4x4<T>::Zero = Matrix4x4<T>(Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero);

		template<typename T>
		const Matrix4x4<T> Matrix4x4<T>::One = Matrix4x4<T>(Scalar<T>::One, Scalar<T>::One, Scalar<T>::One, Scalar<T>::One, Scalar<T>::One);

		template<typename T>
		const Matrix4x4<T> Matrix4x4<T>::Identity = Matrix4x4<T>();

#if ETL_D3D_MATRIX
		template<typename T>
		Matrix4x4<T>::Matrix4x4(T m00, T m01, T m02, T m03
			, T m10, T m11, T m12, T m13
			, T m20, T m21, T m22, T m23
			, T m30, T m31, T m32, T m33)
			: Data{ m00, m01, m02, m03
				  , m10, m11, m12, m13
				  , m20, m21, m22, m23
				  , m30, m31, m32, m33 }
		{
		}
#else // ETL_D3D_MATRIX
		template<typename T>
		Matrix4x4<T>::Matrix4x4(T m00, T m10, T m20, T m30
			, T m01, T m11, T m21, T m31
			, T m02, T m12, T m22, T m32
			, T m03, T m13, T m23, T m33)
			: Data{ m00, m10, m20, m30
				  , m01, m11, m21, m31
				  , m02, m12, m22, m32
				  , m03, m13, m23, m33 }
		{
		}
#endif // ETL_D3D_MATRIX

		template<typename T>
		Matrix4x4<T>::Matrix4x4(T xDiag, T yDiag, T zDiag, T wDiag, T fill)
			: Data{ xDiag, fill, fill, fill
				  , fill, yDiag, fill, fill
				  , fill, fill, zDiag, fill
				  , fill, fill, fill, wDiag }
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

#if ETL_D3D_MATRIX
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
			X = { ETL_INTERNAL_MUL_ROW(x, rhs) };
			Y = { ETL_INTERNAL_MUL_ROW(y, rhs) };
			Z = { ETL_INTERNAL_MUL_ROW(z, rhs) };
			W = { ETL_INTERNAL_MUL_ROW(w, rhs) };
			return *this;
		}

#undef ETL_INTERNAL_MUL_ROW
#undef ETL_INTERNAL_DOT
#else // ETL_D3D_MATRIX
#define ETL_INTERNAL_DOT(c, r, rhs) c.X * rhs.M ## r ## 0 + c.Y * rhs.M ## r ## 1 + c.Z * rhs.M ## r ## 2 + c.W * rhs.M ## r ## 3
#define ETL_INTERNAL_MUL_COL(v, rhs) ETL_INTERNAL_DOT(v, 0, rhs), ETL_INTERNAL_DOT(v, 1, rhs), ETL_INTERNAL_DOT(v, 2, rhs), ETL_INTERNAL_DOT(v, 3, rhs)

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& rhs) const
		{
			return Matrix4x4<T>(ETL_INTERNAL_MUL_COL(X, rhs), ETL_INTERNAL_MUL_COL(Y, rhs), ETL_INTERNAL_MUL_COL(Z, rhs), ETL_INTERNAL_MUL_COL(W, rhs));
		}

		template<typename T>
		Matrix4x4<T>& Matrix4x4<T>::operator*=(const Matrix4x4<T>& rhs)
		{
			Vector4<T> x = X;
			Vector4<T> y = Y;
			Vector4<T> z = Z;
			Vector4<T> w = W;
			X = { ETL_INTERNAL_MUL_COL(x, rhs) };
			Y = { ETL_INTERNAL_MUL_COL(y, rhs) };
			Z = { ETL_INTERNAL_MUL_COL(z, rhs) };
			W = { ETL_INTERNAL_MUL_COL(w, rhs) };
			return *this;
		}

#undef ETL_INTERNAL_MUL_COL
#undef ETL_INTERNAL_DOT
#endif // ETL_D3D_MATRIX

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
#if ETL_D3D_MATRIX
#define ETL_INTERNAL_TRANSFORM_COLUMN(c) M0 ## c * rhs.X + M1 ## c * rhs.Y + M2 ## c * rhs.Z + M3 ## c
			Vector4<T> retVal(ETL_INTERNAL_TRANSFORM_COLUMN(0), ETL_INTERNAL_TRANSFORM_COLUMN(1)
				, ETL_INTERNAL_TRANSFORM_COLUMN(2), ETL_INTERNAL_TRANSFORM_COLUMN(3));
#undef ETL_INTERNAL_TRANSFORM_COLUMN
#else // ETL_D3D_MATRIX
#define ETL_INTERNAL_TRANSFORM_ROW(r) M ## r ## 0 * rhs.X + M ## r ## 1 * rhs.Y + M ## r ## 2 * rhs.Z + M ## r ## 3
			Vector4<T> retVal(ETL_INTERNAL_TRANSFORM_ROW(0), ETL_INTERNAL_TRANSFORM_ROW(1)
				, ETL_INTERNAL_TRANSFORM_ROW(2), ETL_INTERNAL_TRANSFORM_ROW(3));
#undef ETL_INTERNAL_TRANSFORM_ROW
#endif // ETL_D3D_MATRIX
			return retVal.XYZ / retVal.W;
		}

		template<typename T>
		Vector4<T> Matrix4x4<T>::Transform(const Vector4<T>& rhs) const
		{
#if ETL_D3D_MATRIX
#define ETL_INTERNAL_TRANSFORM_COLUMN(c) M0 ## c * rhs.X + M1 ## c * rhs.Y + M2 ## c * rhs.Z + M3 ## c * rhs.W
			Vector4<T> retVal(ETL_INTERNAL_TRANSFORM_COLUMN(0), ETL_INTERNAL_TRANSFORM_COLUMN(1)
				, ETL_INTERNAL_TRANSFORM_COLUMN(2), ETL_INTERNAL_TRANSFORM_COLUMN(3));
#undef ETL_INTERNAL_TRANSFORM_COLUMN
#else // ETL_D3D_MATRIX
#define ETL_INTERNAL_TRANSFORM_ROW(r) M ## r ## 0 * rhs.X + M ## r ## 1 * rhs.Y + M ## r ## 2 * rhs.Z + M ## r ## 3 * rhs.W
			Vector4<T> retVal(ETL_INTERNAL_TRANSFORM_ROW(0), ETL_INTERNAL_TRANSFORM_ROW(1)
				, ETL_INTERNAL_TRANSFORM_ROW(2), ETL_INTERNAL_TRANSFORM_ROW(3));
#undef ETL_INTERNAL_TRANSFORM_ROW
#endif // ETL_D3D_MATRIX
			return retVal / retVal.W;
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeTranslation(const Vector3<T>& translation)
		{
			Matrix4x4<T> retVal;
			retVal.W.XYZ = translation;
			return retVal;
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeTranslation(T x, T y, T z)
		{
			Matrix4x4<T> retVal;
			retVal.W.XYZ = { x, y, z };
			return retVal;
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeRotationX(T radians)
		{
			Matrix4x4<T> retVal;
#if ETL_D3D_MATRIX
			retVal.M11 = Cos(radians);
			retVal.M12 = -Sin(radians);
			retVal.M21 = Sin(radians);
			retVal.M22 = Cos(radians);
#else // ETL_D3D_MATRIX
			retVal.M11 = Cos(radians);
			retVal.M12 = Sin(radians);
			retVal.M21 = -Sin(radians);
			retVal.M22 = Cos(radians);
#endif // ETL_D3D_MATRIX
			return retVal;
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeRotationY(T radians)
		{
			Matrix4x4<T> retVal;
#if ETL_D3D_MATRIX
			retVal.M00 = Cos(radians);
			retVal.M02 = Sin(radians);
			retVal.M20 = -Sin(radians);
			retVal.M22 = Cos(radians);
#else // ETL_D3D_MATRIX
			retVal.M00 = Cos(radians);
			retVal.M02 = -Sin(radians);
			retVal.M20 = Sin(radians);
			retVal.M22 = Cos(radians);
#endif // ETL_D3D_MATRIX
			return retVal;
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeRotationZ(T radians)
		{
			Matrix4x4<T> retVal;
#if ETL_D3D_MATRIX
			retVal.M00 = Cos(radians);
			retVal.M01 = -Sin(radians);
			retVal.M10 = Sin(radians);
			retVal.M11 = Cos(radians);
#else // ETL_D3D_MATRIX
			retVal.M00 = Cos(radians);
			retVal.M01 = Sin(radians);
			retVal.M10 = -Sin(radians);
			retVal.M11 = Cos(radians);
#endif // ETL_D3D_MATRIX
			return retVal;
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeScale(T scale)
		{
			return Matrix4x4<T>(scale, scale, scale);
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeScale(const Vector3<T>& scale)
		{
			return Matrix4x4<T>(scale.X, scale.Y, scale.Z);
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::MakeScale(T x, T y, T z)
		{
			return Matrix4x4<T>(x, y, z);
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