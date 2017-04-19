#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC

#include "Threading/RecursiveMutex_Msvc.h"

#elif ETL_STD

#include "Threading/RecursiveMutex_Std.h"

#endif // ETL_MSVC

#include "Threading/ScopeLock.h"