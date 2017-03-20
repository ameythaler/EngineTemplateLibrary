#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC

#include "Threading/Mutex_Msvc.h"

#elif ETL_STD

#include "Threading/Mutex_Std.h"

#endif // ETL_MSVC

#include "ScopeLock.h"