#include "Utility/DateTime.h"
#include <ctime>

namespace ETL
{
namespace Utility
{
	EtlString DateTime::GetDateString()
	{
		time_t uCurTime = time(0);
		tm* pLocalTime = localtime(&uCurTime);
		EtlStringStream ssTimeStream;
		ssTimeStream << pLocalTime->tm_mon + 1 << '/' << pLocalTime->tm_mday << '/' << pLocalTime->tm_year + 1900;
		return ssTimeStream.str();
	}

	EtlString DateTime::GetTimeString()
	{
		time_t uCurTime = time(0);
		tm* pLocalTime = localtime(&uCurTime);
		EtlStringStream ssTimeStream;
		ssTimeStream << pLocalTime->tm_hour << ':' << pLocalTime->tm_min << ':' << pLocalTime->tm_sec;
		return ssTimeStream.str();
	}
}
}