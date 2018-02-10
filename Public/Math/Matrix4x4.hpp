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

		template<typename T>
		Matrix4x4<T>::Matrix4x4(const T* arrData)
		{
			memcpy(Data, arrData, sizeof(T) * 16);
		}

		template<typename T>
		Matrix4x4<T>& Matrix4x4<T>::operator=(const T* arrData)
		{
			memcpy(Data, arrData, sizeof(T) * 16);
			return *this;
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4<T>& rhs) const
		{
			return Matrix4x4<T>(X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W);
		}

		template<typename T>
		Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4<T>& rhs) const
		{
			return Matrix4x4<T>(X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W);
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