#pragma once

#include "Utility/Platform.h"

#if ETL_MSVC

#include "Threading/Synchronizer_Msvc.h"

#elif ETL_STD

#include "Threading/Synchronizer_Std.h"

#endif // ETL_MSVC