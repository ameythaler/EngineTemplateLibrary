namespace ETL
{
	namespace Math
	{
		template<typename T>
		const Quaternion<T> Quaternion<T>::Identity = Quaternion<T>(Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::Zero, Scalar<T>::One);

		template<typename T>
		Quaternion<T>::Quaternion(const Vector3<T>& axis, T angle)
		{
			T sinA = Sin(angle / Scalar<T>::Two);
			T cosA = Cos(angle / Scalar<T>::Two);
			X = axis.X * sinA;
			Y = axis.Y * sinA;
			Z = axis.Z * sinA;
			W = cosA;
		}

		template<typename T>
		Quaternion<T>::Quaternion(const Vector4<T>& axisAngle)
		{
			T sinA = Sin(axisAngle.W / Scalar<T>::Two);
			T cosA = Cos(axisAngle.W / Scalar<T>::Two);
			X = axisAngle.X * sinA;
			Y = axisAngle.Y * sinA;
			Z = axisAngle.Z * sinA;
			W = cosA;
		}

		template<typename T>
		Quaternion<T>::Quaternion(const T* arrData)
		{
			memcpy(Data, arrData, sizeof(T) * 4);
		}

		template<typename T>
		Quaternion<T>& Quaternion<T>::operator =(const T* arrData)
		{
			memcpy(Data, arrData, sizeof(T) * 4);
			return *this;
		}

		template<typename T>
		Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& rhs) const
		{
			T x = W * rhs.X + X * rhs.W + Y * rhs.Z - Z * rhs.Y;
			T y = W * rhs.Y + Y * rhs.W + Z * rhs.X - X * rhs.Z;
			T z = W * rhs.Z + Z * rhs.W + X * rhs.Y - Y * rhs.X;
			T w = W * rhs.W - X * rhs.X - Y * rhs.Y - Z * rhs.Z;
			return Quaternion<T>(x, y, z, w);
		}

		template<typename T>
		Quaternion<T> Quaternion<T>::operator/(const Quaternion<T>& rhs) const
		{
			T lenSq = rhs.LengthSq();
			T w = (rhs.W * W + rhs.X * X + rhs.Y * Y + rhs.Z * Z) / lenSq;
			T x = (rhs.W * X - rhs.X * W - rhs.Y * Z + rhs.Z * Y) / lenSq;
			T y = (rhs.W * Y + rhs.X * Z - rhs.Y * W - rhs.Z * X) / lenSq;
			T z = (rhs.W * Z + rhs.X * Y + rhs.Y * X - rhs.Z * W) / lenSq;
			return Quaternion<T>(x, y, z, w);
		}

		template<typename T>
		Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& rhs)
		{
			T x = W * rhs.X + X * rhs.W + Y * rhs.Z - Z * rhs.Y;
			T y = W * rhs.Y + Y * rhs.W + Z * rhs.X - X * rhs.Z;
			T z = W * rhs.Z + Z * rhs.W + X * rhs.Y - Y * rhs.X;
			T w = W * rhs.W - X * rhs.X - Y * rhs.Y - Z * rhs.Z;
			X = x;
			Y = y;
			Z = z;
			W = w;
			return *this;
		}

		template<typename T>
		Quaternion<T>& Quaternion<T>::operator/=(const Quaternion<T>& rhs)
		{
			T lenSq = rhs.LengthSq();
			T w = (rhs.W * W + rhs.X * X + rhs.Y * Y + rhs.Z * Z) / lenSq;
			T x = (rhs.W * X - rhs.X * W - rhs.Y * Z + rhs.Z * Y) / lenSq;
			T y = (rhs.W * Y + rhs.X * Z - rhs.Y * W - rhs.Z * X) / lenSq;
			T z = (rhs.W * Z + rhs.X * Y + rhs.Y * X - rhs.Z * W) / lenSq;
			X = x;
			Y = y;
			Z = z;
			W = w;
			return *this;
		}

		template<typename T>
		Quaternion<T>& Quaternion<T>::Normalize()
		{
			return *this /= Length();
		}

		template<typename T>
		Quaternion<T> Quaternion<T>::Normalized() const
		{
			return *this / Length();
		}

		template<typename T>
		Quaternion<T>& Quaternion<T>::Conjugate()
		{
			X = -X;
			Y = -Y;
			Z = -Z;
			return *this;
		}

		template<typename T>
		T Quaternion<T>::AxisAngle(Vector3<T>& outAxis) const
		{
			T cosA = W;
			T angle = ACos(cosA) * Scalar<T>::Two;
			T sinA = Sqrt(Scalar<T>::One - cosA * cosA);
			sinA = (Abs(sinA) >= Scalar<T>::Epsilon) ? sinA : Scalar<T>::One;
			outAxis.X = X / sinA;
			outAxis.Y = Y / sinA;
			outAxis.Z = Z / sinA;
			return angle;
		}

		template<typename T>
		Vector4<T> Quaternion<T>::AxisAngle() const
		{
			T cosA = W;
			T angle = ACos(cosA) * Scalar<T>::Two;
			T sinA = Sqrt(Scalar<T>::One - cosA * cosA);
			sinA = (Abs(sinA) >= Scalar<T>::Epsilon) ? sinA : Scalar<T>::One;
			return Vector4<T>(X / sinA, Y / sinA, Z / sinA, angle);
		}

		template<typename T>
		Quaternion<T>::operator WideString() const
		{
			WideStringStream stream;
			stream << *this;
			return stream.str();
		}

		template<typename T>
		WideOStream& operator<<(WideOStream& out, const Quaternion<T>& vec)
		{
			out << L"(" << vec.X << L", " << vec.Y << L", " << vec.Z << L", " << vec.W << L")";
			return out;
		}

		template<typename T>
		Quaternion<T>::operator MbString() const
		{
			MbStringStream stream;
			stream << *this;
			return stream.str();
		}

		template<typename T>
		MbOStream& operator<<(MbOStream& out, const Quaternion<T>& vec)
		{
			out << "(" << vec.X << ", " << vec.Y << ", " << vec.Z << ", " << vec.W << ")";
			return out;
		}
	}
}