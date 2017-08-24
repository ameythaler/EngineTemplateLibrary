#pragma once

#include "Utility/Types.h"

namespace ETL
{
namespace Utility
{
	class LogOutStream : public EtlOStream
	{
		//friend EtlOStream& operator<<(EtlOStream& out, const EtlString& arg);

	public:
		LogOutStream();

	protected:
		EtlStringBuf& m_StrBuf;
	};
}
}