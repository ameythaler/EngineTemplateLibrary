#include "Math/Matrix4x4.h"

namespace ETL
{
	namespace Math
	{
#define ETL_INTERNAL_EXPLICIT_INST_DEF(T) template struct Matrix4x4<T>

		ETL_INTERNAL_EXPLICIT_INST_DEF(float);
		ETL_INTERNAL_EXPLICIT_INST_DEF(double);

#undef ETL_INTERNAL_EXPLICIT_INST_DEF

		// #TODO Not sure these are needed
		template<>
		MbOStream& operator<<(MbOStream& out, const Matrix4x4<uint8>& mat)
		{
			out << "[" << mat.X << ", " << mat.Y << ", " << mat.Z << ", " << mat.W << "]";
			return out;
		}

		template<>
		MbOStream& operator<<(MbOStream& out, const Matrix4x4<int8>& mat)
		{
			out << "[" << mat.X << ", " << mat.Y << ", " << mat.Z << ", " << mat.W << "]";
			return out;
		}
	}
}