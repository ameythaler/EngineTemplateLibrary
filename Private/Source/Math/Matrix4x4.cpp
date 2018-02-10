#include "Math/Matrix4x4.h"

namespace ETL
{
	namespace Math
	{
#define ETL_INTERNAL_EXPLICIT_INST_DEF(T) template struct Matrix4x4<T>

		ETL_INTERNAL_EXPLICIT_INST_DEF(float);
		ETL_INTERNAL_EXPLICIT_INST_DEF(double);
		ETL_INTERNAL_EXPLICIT_INST_DEF(int32);
		ETL_INTERNAL_EXPLICIT_INST_DEF(uint32);
		ETL_INTERNAL_EXPLICIT_INST_DEF(int64);
		ETL_INTERNAL_EXPLICIT_INST_DEF(uint64);
		ETL_INTERNAL_EXPLICIT_INST_DEF(int16);
		ETL_INTERNAL_EXPLICIT_INST_DEF(uint16);
		ETL_INTERNAL_EXPLICIT_INST_DEF(int8);
		ETL_INTERNAL_EXPLICIT_INST_DEF(uint8);

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