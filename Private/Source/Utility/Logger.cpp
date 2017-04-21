#include "Utility/Logger.h"
#include "Utility/DateTime.h"
#include "Filesystem/Directory.h"
#include "Filesystem/BaseFile.h"
#include <cstdio>

#if ETL_WIN
#include "Windows.h"
#endif // ETL_WIN

using ETL::Filesystem::Directory;
using ETL::Threading::ScopeWriteLock;
using ETL::Filesystem::BaseFile;

namespace
{
	std::FILE* s_pLogFile = nullptr;
	const wchar_t* szErrorText = L"ERROR: ";
}

namespace ETL
{
namespace Utility
{
	ETL_IMPLEMENT_SINGLETON(Logger);

	Logger::Logger() : m_bLogToWindow(false), m_bLogToFile(false), m_bLogDebug(false)
	{

	}

	Logger::~Logger()
	{

	}

	void Logger::Create(bool bLogToWindow, bool bLogToFile, bool bLogDebug, const EtlString& applicationName)
	{
		m_bLogToWindow = bLogToWindow;
		m_bLogToFile = bLogToFile;

#if ETL_WIN
		if (m_bLogToWindow) // Open log window
		{
			m_bCreatedConsole = false;
			if (GetConsoleWindow() == nullptr)
			{
				m_bCreatedConsole = true;
				AllocConsole();
				freopen("CONOUT$", "w", stdout);
				freopen("CONOUT$", "w", stderr);
			}
		}
#endif // ETL_WIN

		if (m_bLogToFile) // If we're logging to a file, we need to shift our log file history.
		{
			EtlString szLogFile;
			int nLogFileCount = -1;
			if (Directory::FileExists(L"Log.txt")) // Do we have a pre-existing log file?
				nLogFileCount = 0;

			// Count the number of historical log files
			for (int fileIdx = 1; fileIdx < kNumLogs; ++fileIdx)
			{
				EtlStringStream ssFileName;
				ssFileName << L"Log" << fileIdx << L".txt";
				szLogFile = ssFileName.str();
				if (Directory::FileExists(szLogFile))
					nLogFileCount++;
				else
					break;
			}

			// If we have the maximum number of historical logs, then delete the last one.
			if (nLogFileCount == kNumLogs - 1)
			{
				EtlStringStream ssLastLogName;
				ssLastLogName << L"Log" << kNumLogs - 1 << L".txt";
				Directory::RemoveFile(ssLastLogName.str());
				nLogFileCount--;
			}

			// Rename each historical log file to the next oldest file name.
			for (int fileIdx = nLogFileCount; fileIdx > 0; --fileIdx)
			{
				EtlStringStream ssNameStream;
				ssNameStream << L"Log" << fileIdx + 1 << L".txt";
				EtlString szLogFileDestination = ssNameStream.str();
				ssNameStream.str(L"");
				ssNameStream << L"Log" << fileIdx << L".txt";
				szLogFile = ssNameStream.str();
				Directory::RenameFileOrDirectory(szLogFile, szLogFileDestination);
			}

			// Rename our last active log file to be the first historical log file.
			if (nLogFileCount > -1)
				Directory::RenameFileOrDirectory(L"Log.txt", L"Log1.txt");

			// Open the new active log file.
#if ETL_WIN
			_wfopen_s(&s_pLogFile, L"Log.txt", L"w");
#else // ETL_WIN
			s_pLogFile = fopen("Log.txt", "w");
#endif // ETL_WIN
		}

		// Output an initialization message.
		m_bLogDebug = true;
		LogOut(applicationName + L" log initialized " + DateTime::GetDateString());
		m_bLogDebug = bLogDebug;
	}

	void Logger::Destroy()
	{
#if Q_WIN
		if (m_bLogToWindow && m_bCreatedConsole)
		{
			fclose(stdout);
			FreeConsole();
		}
#endif

		if (m_bLogToFile)
		{
			fclose(s_pLogFile);
		}
	}

	void Logger::LogOut(EtlStringStream& ssLogStream)
	{
		if (!m_bLogDebug)
			return;
		{
			ScopeWriteLock lock(m_LogMutex);
			ssLogStream << std::endl;
			EtlString logString = L'(' + DateTime::GetTimeString() + L") " + ssLogStream.str();

			if (m_bLogToWindow)
				wprintf(logString.c_str());

			if (m_bLogToFile)
			{
				fwprintf(s_pLogFile, logString.c_str());
				fflush(s_pLogFile);
			}
		}
	}

	void Logger::LogOut(const EtlString& message)
	{
		if (!m_bLogDebug)
			return;
		{
			ScopeWriteLock lock(m_LogMutex);
			EtlString szMsg;
			szMsg = L'(' + DateTime::GetTimeString() + L") " + message + L'\n';
			if (m_bLogToWindow)
				wprintf(szMsg.c_str());

			if (m_bLogToFile)
			{
				fwprintf(s_pLogFile, szMsg.c_str());
				fflush(s_pLogFile);
			}
		}
	}

	void Logger::LogOut(const wchar_t* szMessage, ...)
	{
		if (!m_bLogDebug)
			return;
		{
			ScopeWriteLock lock(m_LogMutex);
			va_list args1;
			va_start(args1, szMessage);
			va_list args2;
			va_copy(args2, args1);
			EtlString szMsg;
			szMsg = L'(' + DateTime::GetTimeString() + L") " + szMessage + L'\n';
			if (m_bLogToWindow)
				vwprintf(szMsg.c_str(), args1);

			if (m_bLogToFile)
			{
				vfwprintf(s_pLogFile, szMsg.c_str(), args2);
				fflush(s_pLogFile);
			}

			va_end(args1);
			va_end(args2);
		}
	}

	void Logger::LogOutError(EtlStringStream& ssLogStream)
	{
		ScopeWriteLock lock(m_LogMutex);
		ssLogStream << std::endl;
		EtlString logString = L'(' + DateTime::GetTimeString() + L") " + szErrorText + ssLogStream.str();

		if (m_bLogToWindow)
			wprintf(logString.c_str());

		if (m_bLogToFile)
		{
			fwprintf(s_pLogFile, logString.c_str());
			fflush(s_pLogFile);
		}
	}

	void Logger::LogOutError(const EtlString& message)
	{
		ScopeWriteLock lock(m_LogMutex);
		EtlString szMsg;
		szMsg = L'(' + DateTime::GetTimeString() + L") " + szErrorText + message + L'\n';
		if (m_bLogToWindow)
			wprintf(szMsg.c_str());

		if (m_bLogToFile)
		{
			fwprintf(s_pLogFile, szMsg.c_str());
			fflush(s_pLogFile);
		}
	}

	void Logger::LogOutError(const wchar_t* szMessage, ...)
	{
		ScopeWriteLock lock(m_LogMutex);
		va_list args1;
		va_start(args1, szMessage);
		va_list args2;
		va_copy(args2, args1);
		EtlString szMsg;
		szMsg = L'(' + DateTime::GetTimeString() + L") " + szErrorText + szMessage + L'\n';
		if (m_bLogToWindow)
			vwprintf(szMsg.c_str(), args1);

		if (m_bLogToFile)
		{
			vfwprintf(s_pLogFile, szMsg.c_str(), args2);
			fflush(s_pLogFile);
		}

		va_end(args1);
		va_end(args2);
	}
}
}
