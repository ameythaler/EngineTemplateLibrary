namespace ETL
{
	namespace Math
	{
		template<typename T>
		const Vector4<T> Vector4<T>::Zero = Vector4<T>();

		template<typename T>
		const Vector4<T> Vector4<T>::One = Vector4<T>(Scalar<T>::One, Scalar<T>::One, Scalar<T>::One, Scalar<T>::One);

		template<typename T>
		const Vector4<T> Vector4<T>::XAxis = Vector4<T>(Scalar<T>::One, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero);

		template<typename T>
		const Vector4<T> Vector4<T>::YAxis = Vector4<T>(Scalar<T>::Zero, Scalar<T>::One, Scalar<T>::Zero, Scalar<T>::Zero);

		template<typename T>
		const Vector4<T> Vector4<T>::ZAxis = Vector4<T>(Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::One, Scalar<T>::Zero);

		template<typename T>
		Vector4<T>::Vector4(const T* arrData)
		{
			memcpy(Data, arrData, sizeof(T) * 4);
		}

		template<typename T>
		Vector4<T>& Vector4<T>::operator =(const Vector4& rhs)
		{
			memcpy(Data, rhs.Data, sizeof(T) * 4);
			return *this;
		}

		template<typename T>
		Vector4<T>& Vector4<T>::operator =(const T* arrData)
		{
			memcpy(Data, arrData, sizeof(T) * 4);
			return *this;
		}

		template<typename T>
		Vector4<T>& Vector4<T>::Normalize()
		{
			return *this /= Length();
		}

		template<typename T>
		Vector4<T> Vector4<T>::Normalized() const
		{
			return *this / Length();
		}

		template<typename T>
		Vector4<T> Vector4<T>::Project(const Vector4<T>& axis) const
		{
			return Dot(axis) * axis;
		}

		template<typename T>
		Vector4<T> Vector4<T>::Cross(const Vector4<T>& rhs) const
		{
			return Vector4<T>(X * rhs.Z - Z * rhs.Y, -(X * rhs.Z - Z * rhs.X), X * rhs.Y - Y * rhs.X, W);
		}

		template<typename T>
		Vector4<T>::operator WideString() const
		{
			WideStringStream stream;
			stream << *this;
			return stream.str();
		}

		template<typename T>
		WideOStream& operator<<(WideOStream& out, const Vector4<T>& vec)
		{
			out << L"<" << vec.X << L", " << vec.Y << L", " << vec.Z << L", " << vec.W << L">";
			return out;
		}

		template<typename T>
		Vector4<T>::operator MbString() const
		{
			MbStringStream stream;
			stream << *this;
			return stream.str();
		}

		template<typename T>
		MbOStream& operator<<(MbOStream& out, const Vector4<T>& vec)
		{
			out << "<" << vec.X << ", " << vec.Y << ", " << vec.Z << ", " << vec.W << ">";
			return out;
		}
	}
}