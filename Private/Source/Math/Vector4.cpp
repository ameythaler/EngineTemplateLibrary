#include "Math/Vector4.h"

namespace ETL
{
	namespace Math
	{
#define ETL_INTERNAL_EXPLICIT_INST_DEF(T) template struct Vector4<T>

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

		template<>
		MbOStream& operator<<(MbOStream& out, const Vector4<uint8>& vec)
		{
			out << "<" << (uint32)vec.X << ", " << (uint32)vec.Y << ", " << (uint32)vec.Z << ", " << (uint32)vec.W << ">";
			return out;
		}

		template<>
		MbOStream& operator<<(MbOStream& out, const Vector4<int8>& vec)
		{
			out << "<" << (int32)vec.X << ", " << (int32)vec.Y << ", " << (int32)vec.Z << ", " << (int32)vec.W << ">";
			return out;
		}
	}
}