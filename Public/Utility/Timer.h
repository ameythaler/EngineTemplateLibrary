#pragma once

#include "Utility/Platform.h"

#if ETL_WIN

#include "Utility/Timer_Win.h"

#elif ETL_POSIX

#include "Utility/Timer_Posix.h"

#endif // ETL_WIN