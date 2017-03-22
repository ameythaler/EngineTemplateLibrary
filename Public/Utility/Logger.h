#pragma once

#include "Utility/Platform.h"

#include "Utility/Types.h"
#include "Utility/Macros.h"
#include "Threading/Mutex.h"
#include <cstdarg>

namespace ETL
{
namespace Utility
{
	class Logger
	{
		ETL_DECLARE_SINGLETON(Logger);

	public:
		void Create(bool bLogToWindow, bool bLogToFile, bool bLogDebug, EtlString applicationName);
		void Destroy();
		void LogOut(const EtlString& message);
		void LogOut(EtlStringStream& ssLogStream);
		void LogOut(const wchar_t* szMessage, ...);
		void LogOutError(const EtlString& message);
		void LogOutError(EtlStringStream& ssLogStream);
		void LogOutError(const wchar_t* szMessage, ...);

	private:
		bool m_bLogToWindow;
		bool m_bLogToFile;
		bool m_bLogDebug;
		static const int kNumLogs = 10;
		Threading::Mutex m_LogMutex;

#if ETL_WIN
		bool m_bCreatedConsole;
#endif
	};

	struct LogRAII
	{
		LogRAII(bool bLogToWindow, bool bLogToFile, bool bLogDebug, EtlString applicationName)
		{
			Logger::Instance().Create(bLogToWindow, bLogToFile, bLogDebug, applicationName);
		}

		~LogRAII()
		{
			Logger::Instance().Destroy();
		}
	};
}
}

#if ETL_LOGGING

#define ETL_LOGINIT(logTowindow, logToFile, logDebug, appName)
#define ETL_LOGDBG(message)
#define ETL_LOGERR(message)

#else

#define ETL_LOGINIT(logToWindow, logToFile, logDebug, appName) ETL::Utility::LogRAII gLog(logToWindow, logToFile, logDebug, appName)

#if ETL_MSVC

#define ETL_LOGDBG(message, ...) ETL::Utility::Logger::Instance().LogOut(message, __VA_ARGS__)
#define ETL_LOGERR(message, ...) ETL::Utility::Logger::Instance().LogOutError(message, __VA_ARGS__)

#else

#define ETL_LOGDBG(message, ...) ETL::Utility::Logger::Instance().LogOut(message, ##__VA_ARGS__)
#define ETL_LOGERR(message, ...) ETL::Utility::Logger::Instance().LogOutError(message, ##__VA_ARGS__)

#endif // Q_WIN

#endif // ETL_LOGGING

