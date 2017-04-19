namespace ETL
{
namespace Math
{
	template<typename T>
	const Vector2<T> Vector2<T>::Zero = Vector2<T>();

	template<typename T>
	const Vector2<T> Vector2<T>::One = Vector2<T>(Scalar<T>::One, Scalar<T>::One);

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
	Vector2<T>::operator EtlString() const
	{
		EtlStringStream stream;
		stream << *this;
		return stream.str();
	}

	template<typename T>
	std::wofstream& operator<<(std::wofstream& out, const Vector2<T>& vec)
	{
		//out << L"<" << vec.X << L", " << vec.Y << L">";
		return out;
	}
}
}