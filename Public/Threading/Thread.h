#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC

#include "Threading/Thread_Msvc.h"

#elif ETL_STD

#include "Threading/Thread_Std.h"

#endif