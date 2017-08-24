namespace ETL
{
	namespace Math
	{
		template<typename T>
		const Vector3<T> Vector3<T>::Zero = Vector3<T>();

		template<typename T>
		const Vector3<T> Vector3<T>::One = Vector3<T>(Scalar<T>::One, Scalar<T>::One, Scalar<T>::One);

		template<typename T>
		const Vector3<T> Vector3<T>::XAxis = Vector3<T>(Scalar<T>::One, Scalar<T>::Zero, Scalar<T>::Zero);

		template<typename T>
		const Vector3<T> Vector3<T>::YAxis = Vector3<T>(Scalar<T>::Zero, Scalar<T>::One, Scalar<T>::Zero);

		template<typename T>
		const Vector3<T> Vector3<T>::ZAxis = Vector3<T>(Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::One);

		template<typename T>
		Vector3<T>::Vector3(const T* arrData)
		{
			memcpy(Data, arrData, sizeof(T) * 3);
		}

		template<typename T>
		Vector3<T>& Vector3<T>::operator =(const Vector3& rhs)
		{
			memcpy(Data, rhs.Data, sizeof(T) * 3);
			return *this;
		}

		template<typename T>
		Vector3<T>& Vector3<T>::operator =(const T* arrData)
		{
			memcpy(Data, arrData, sizeof(T) * 3);
			return *this;
		}

		template<typename T>
		Vector3<T>& Vector3<T>::Normalize()
		{
			return *this /= Length();
		}

		template<typename T>
		Vector3<T> Vector3<T>::Normalized() const
		{
			return *this / Length();
		}

		template<typename T>
		Vector3<T> Vector3<T>::Project(const Vector3<T>& axis) const
		{
			return Dot(axis) * axis;
		}

		template<typename T>
		Vector3<T> Vector3<T>::Cross(const Vector3<T>& rhs) const
		{
			return Vector3<T>(X * rhs.Z - Z * rhs.Y, -(X * rhs.Z - Z * rhs.X), X * rhs.Y - Y * rhs.X);
		}

		template<typename T>
		Vector3<T>::operator WideString() const
		{
			WideStringStream stream;
			stream << *this;
			return stream.str();
		}

		template<typename T>
		WideOStream& operator<<(WideOStream& out, const Vector3<T>& vec)
		{
			out << L"<" << vec.X << L", " << vec.Y << L", " << vec.Z << L">";
			return out;
		}

		template<typename T>
		Vector3<T>::operator MbString() const
		{
			MbStringStream stream;
			stream << *this;
			return stream.str();
		}

		template<typename T>
		MbOStream& operator<<(MbOStream& out, const Vector3<T>& vec)
		{
			out << "<" << vec.X << ", " << vec.Y << ", " << vec.Z << ">";
			return out;
		}
	}
}