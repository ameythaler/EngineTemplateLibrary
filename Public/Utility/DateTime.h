#pragma once

#include "Utility/Types.h"

namespace ETL
{
namespace Utility
{
	class DateTime
	{
	public:
		static EtlString GetDateString();
		static EtlString GetTimeString();
	};
}
}