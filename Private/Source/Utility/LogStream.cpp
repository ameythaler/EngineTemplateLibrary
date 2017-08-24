#include "Utility/LogStream.h"
#include "Utility/Logger.h"

namespace ETL
{
namespace Utility
{
	LogOutStream::LogOutStream()
		: EtlOStream(&m_StrBuf)
		, m_StrBuf(Logger::Instance().m_StringBuf)
	{
		
	}
}
}