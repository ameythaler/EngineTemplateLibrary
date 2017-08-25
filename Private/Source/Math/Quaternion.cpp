#include "Math/Quaternion.h"

namespace ETL
{
	namespace Math
	{
#define ETL_INTERNAL_EXPLICIT_INST_DEF(T) template struct Quaternion<T>

		ETL_INTERNAL_EXPLICIT_INST_DEF(float);
		ETL_INTERNAL_EXPLICIT_INST_DEF(double);

#undef ETL_INTERNAL_EXPLICIT_INST_DEF
	}
}