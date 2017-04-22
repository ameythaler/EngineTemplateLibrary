namespace ETL
{
namespace Math
{
	template<typename T>
	const Vector2<T> Vector2<T>::Zero = Vector2<T>();

	template<typename T>
	const Vector2<T> Vector2<T>::One = Vector2<T>(Scalar<T>::One, Scalar<T>::One);

	template<typename T>
	const Vector2<T> Vector2<T>::XAxis = Vector2<T>(Scalar<T>::One, Scalar<T>::Zero);

	template<typename T>
	const Vector2<T> Vector2<T>::YAxis = Vector2<T>(Scalar<T>::Zero, Scalar<T>::One);

	template<typename T>
	Vector2<T>::Vector2(const T* arrData)
	{
		memcpy(Data, arrData, sizeof(T) * 2);
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator =(const Vector2& rhs)
	{
		memcpy(Data, rhs.Data, sizeof(T) * 2);
		return *this;
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator =(const T* arrData)
	{
		memcpy(Data, arrData, sizeof(T) * 2);
	}

	template<typename T>
	Vector2<T>& Vector2<T>::Normalize()
	{
		return *this /= Length();
	}

	template<typename T>
	Vector2<T> Vector2<T>::Normalized() const
	{
		return *this / Length();
	}

	template<typename T>
	Vector2<T> Vector2<T>::Project(const Vector2<T>& axis) const
	{
		return Dot(axis) * axis;
	}

	template<typename T>
	Vector2<T>::operator WideString() const
	{
		WideStringStream stream;
		stream << *this;
		return stream.str();
	}

	template<typename T>
	WideOStream& operator<<(WideOStream& out, const Vector2<T>& vec)
	{
		out << L"<" << vec.X << L", " << vec.Y << L">";
		return out;
	}

	template<typename T>
	Vector2<T>::operator MbString() const
	{
		MbStringStream stream;
		stream << *this;
		return stream.str();
	}

	template<typename T>
	MbOStream& operator<<(MbOStream& out, const Vector2<T>& vec)
	{
		out << "<" << vec.X << ", " << vec.Y << ">";
		return out;
	}
}
}