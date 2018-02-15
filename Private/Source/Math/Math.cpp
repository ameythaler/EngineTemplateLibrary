#define _USE_MATH_DEFINES
#include "Math/Math.h"
#include <limits.h>

namespace ETL
{
	namespace Math
	{
#define ETL_INTERNAL_EXPLICIT_DEF_SCALAR(T, zero, one, two, four, epsilon) const T Scalar<T>::Zero = zero; \
	const T Scalar<T>::One = one; \
	const T Scalar<T>::Two = two; \
	const T Scalar<T>::Four = four; \
	const T Scalar<T>::Epsilon = epsilon; \
	const T Scalar<T>::Pi = (T)M_PI; \
	const T Scalar<T>::Pi2 = (T)M_PI * two; \
	const T Scalar<T>::Pi4 = (T)M_PI * four; \
	const T Scalar<T>::PiOver2 = (T)M_PI / two; \
	const T Scalar<T>::PiOver4 = (T)M_PI / four; \
	bool Scalar<T>::Equal(T rhs, T lhs) \
	{ \
		return Abs(rhs - lhs) <= Epsilon; \
	} \
	bool Scalar<T>::NotEqual(T rhs, T lhs) \
	{ \
		return Abs(rhs - lhs) > Epsilon; \
	} \
	template struct Scalar<T>

	ETL_INTERNAL_EXPLICIT_DEF_SCALAR(float, 0.0f, 1.0f, 2.0f, 4.0f, std::numeric_limits<float>::epsilon());
	ETL_INTERNAL_EXPLICIT_DEF_SCALAR(double, 0.0, 1.0, 2.0, 4.0, std::numeric_limits<double>::epsilon());
	ETL_INTERNAL_EXPLICIT_DEF_SCALAR(int32, 0, 1, 2, 4, 0);
	ETL_INTERNAL_EXPLICIT_DEF_SCALAR(uint32, 0u, 1u, 2u, 4u, 0u);
	ETL_INTERNAL_EXPLICIT_DEF_SCALAR(int64, 0, 1, 2, 4, 0);
	ETL_INTERNAL_EXPLICIT_DEF_SCALAR(uint64, 0u, 1u, 2u, 4u, 0u);
	ETL_INTERNAL_EXPLICIT_DEF_SCALAR(int16, 0, 1, 2, 4, 0);
	ETL_INTERNAL_EXPLICIT_DEF_SCALAR(uint16, 0u, 1u, 2u, 4u, 0u);
	ETL_INTERNAL_EXPLICIT_DEF_SCALAR(int8, 0, 1, 2, 4, 0);
	ETL_INTERNAL_EXPLICIT_DEF_SCALAR(uint8, 0u, 1u, 2u, 4u, 0u);

#undef ETL_INTERNAL_EXPLICIT_DEF_SCALAR
	}
}