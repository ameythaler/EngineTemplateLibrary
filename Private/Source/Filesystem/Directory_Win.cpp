#include "Utility/Platform.h"

#if ETL_WIN

#include "Filesystem/Directory.h"
#include "Memory/MemTrack.h"
#include "Windows.h"
#include "Shlobj.h"

namespace ETL
{
namespace Filesystem
{
	const EtlChar Directory::s_kDivider = ETL_TEXT('\\');

	bool Directory::FileExists(const EtlString& filename)
	{
		return GetFileAttributes(filename.c_str()) != INVALID_FILE_ATTRIBUTES;
	}

	void Directory::RemoveFile(const EtlString& filename)
	{
#if ETL_UNICODE
		_wremove(filename.c_str());
#else // ETL_UNICODE
		remove(filename.c_str());
#endif // ETL_UNICODE
	}

	void Directory::RenameFileOrDirectory(const EtlString& oldName, const EtlString& newName)
	{
#if ETL_UNICODE
		_wrename(oldName.c_str(), newName.c_str());
#else // ETL_UNICODE
		rename(oldName.c_str(), newName.c_str());
#endif // ETL_UNICODE
	}

	bool Directory::DirectoryExists(const EtlString& dirName)
	{
		DWORD attribs = GetFileAttributes(dirName.c_str());
		return attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY);
	}

	void Directory::Create_Directory(const EtlString& dirName)
	{
		CreateDirectory(dirName.c_str(), nullptr);
	}

	bool Directory::IsDirectoryEmpty(const EtlString& dirName)
	{
		EtlString dir;
		if (dirName.back() != ETL_TEXT('*'))
			dir = ConcatPath(dirName, ETL_TEXT("*"));
		else
			dir = dirName;

		WIN32_FIND_DATAW findResult;
		HANDLE hSearch = FindFirstFile(dir.c_str(), &findResult);
		const EtlString thisDir(ETL_TEXT("."));
		const EtlString prevDir(ETL_TEXT(".."));
		while (hSearch != INVALID_HANDLE_VALUE)
		{
			if (thisDir != findResult.cFileName && prevDir != findResult.cFileName)
				return false;

			if (!FindNextFile(hSearch, &findResult))
			{
				FindClose(hSearch);
				hSearch = INVALID_HANDLE_VALUE;
			}
		}
		return true;
	}

	EtlString Directory::GetUserDirectory()
	{
		static auto _GetUserDirectory = []() {
			wchar_t* tempPath;
			SHGetKnownFolderPath(FOLDERID_Profile, 0, nullptr, &tempPath);
			EtlString retVal(WideStringToEtlString(tempPath));
			CoTaskMemFree(tempPath);
			return retVal;
		};
		static EtlString userDirectory = _GetUserDirectory();
		return userDirectory;
	}

	EtlString Directory::GetWorkingDirectory()
	{
		static auto _GetWorkingDirectory = []() {
			DWORD pathLen = GetCurrentDirectory(0, nullptr);
			EtlChar* tempPath = ETL_NEW("ETL::Filesystem::Directory::tempPath") EtlChar[pathLen];
			GetCurrentDirectory(pathLen, tempPath);
			EtlString retVal(tempPath);
			ETL_DELETE[] tempPath;
			return retVal;
		};
		static EtlString workingDirectory = _GetWorkingDirectory();
		return workingDirectory;
	}

	EtlString Directory::GetExecutableDirectory()
	{
		static auto _GetExecutableDirectory = []() {
			EtlString retVal;
			MbCharArrayToEtlString(retVal, _pgmptr);
			auto lastDir = retVal.find_last_of(ETL_TEXT('\\'));
			retVal = retVal.substr(0, lastDir);
			return retVal;
		};
		static EtlString executableDirectory = _GetExecutableDirectory();
		return executableDirectory;
	}

	EtlString Directory::GetLocalAppDataDirectory()
	{
		static auto _GetLocalAppDataDirectory = []() {
			wchar_t* tempPath;
			SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &tempPath);
			EtlString retVal(WideStringToEtlString(tempPath));
			CoTaskMemFree(tempPath);
			return retVal;
		};
		static EtlString localAppDataDirectory = _GetLocalAppDataDirectory();
		return localAppDataDirectory;
	}

	EtlString Directory::GetDocumentsDirectory()
	{
		static auto _GetDocumentsDirectory = []() {
			wchar_t* tempPath;
			SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &tempPath);
			EtlString retVal(WideStringToEtlString(tempPath));
			CoTaskMemFree(tempPath);
			return retVal;
		};
		static EtlString documentsDirectory = _GetDocumentsDirectory();
		return documentsDirectory;
	}

	EtlString Directory::GetDesktopDirectory()
	{
		static auto _GetDesktopDirectory = []() {
			wchar_t* tempPath;
			SHGetKnownFolderPath(FOLDERID_Desktop, 0, nullptr, &tempPath);
			EtlString retVal(WideStringToEtlString(tempPath));
			CoTaskMemFree(tempPath);
			return retVal;
		};
		static EtlString desktopDirectory = _GetDesktopDirectory();
		return desktopDirectory;
	}

	std::vector<EtlString> Directory::ListFilesOrDirectories(const EtlString& dirName, uint8 findFlags, bool bIncludeSpecialDirs)
	{
		std::vector<EtlString> retVal;

		EtlString dir;
		if (dirName.back() != ETL_TEXT('*'))
			dir = ConcatPath(dirName, ETL_TEXT("*"));
		else
			dir = dirName;

		WIN32_FIND_DATAW findResult;
		HANDLE hSearch = FindFirstFile(dir.c_str(), &findResult);
		const EtlString thisDir(ETL_TEXT("."));
		const EtlString prevDir(ETL_TEXT(".."));
		while (hSearch != INVALID_HANDLE_VALUE)
		{
			if (bIncludeSpecialDirs || (thisDir != findResult.cFileName && prevDir != findResult.cFileName))
			{
				switch (findFlags)
				{
				case 1: // Directories only
					if (findResult.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
						retVal.push_back(findResult.cFileName);
					break;
				case 2: // Files only
					if (!(findResult.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
						retVal.push_back(findResult.cFileName);
					break;
				case 3: // Files and directories
					retVal.push_back(findResult.cFileName);
					break;
				}
			}

			if (!FindNextFileW(hSearch, &findResult))
			{
				FindClose(hSearch);
				hSearch = INVALID_HANDLE_VALUE;
			}
		}

		return retVal;
	}

	void Directory::_RemoveDirectory(const EtlString& dirName)
	{
		RemoveDirectory(dirName.c_str());
	}
}
}

#endif // ETL_WIN