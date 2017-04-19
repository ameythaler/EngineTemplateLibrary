#include "Utility/Platform.h"

#if ETL_POSIX

#include "Filesystem/Directory.h"
#include "Memory/MemTrack.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <mach-o/dyld.h>
#include <vector>
#include <sys/param.h>

namespace ETL
{
namespace Filesystem
{
	const EtlChar Directory::s_kDivider = ETL_TEXT('/');

	bool Directory::FileExists(const EtlString &filename)
	{
		LocalCharPtr filenameMb(filename);
		if (FILE* file = fopen(filenameMb, "r"))
		{
			fclose(file);
			return true;
		}
		return false;
	}

	void Directory::RemoveFile(const EtlString &filename)
	{
		LocalCharPtr filenameMb(filename);
		std::remove(filenameMb);
	}

	void Directory::RenameFileOrDirectory(const EtlString& oldFilename, const EtlString& newFilename)
	{
		LocalCharPtr oldNameMb(oldFilename);
		LocalCharPtr newNameMb(newFilename);
		std::rename(oldNameMb, newNameMb);
	}

	bool Directory::DirectoryExists(const EtlString &dirName)
	{
		LocalCharPtr dirNameMb(dirName);
		struct stat dirStat;
		stat(dirNameMb, &dirStat);
		if (dirStat.st_mode & S_IFDIR)
			return true;
		else
			return false;
	}

	void Directory::Create_Directory(const EtlString &dirName)
	{
		LocalCharPtr dirNameMb(dirName);
		mkdir(dirNameMb, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);
	}

	bool Directory::IsDirectoryEmpty(const EtlString& dirName)
	{
		EtlString dir;
		if (dirName.back() == ETL_TEXT('*'))
			dir = RemoveLastElement(dirName);
		else
			dir = dirName;

		LocalCharPtr searchDir(dir);
		DIR* pSearch;
		struct dirent* pFindResult;
		struct stat dirStat;
		MbString thisDir(".");
		MbString prevDir("..");
		MbString dsStore(".DS_Store");

		if ((pSearch = opendir(searchDir)))
		{
			MbString dirString(searchDir);
			dirString += '/';
			while ((pFindResult = readdir(pSearch)))
			{
				char* resName = pFindResult->d_name;
				bool bIsSpecial = (thisDir == resName) || (prevDir == resName) || (dsStore == resName);
				if (!bIsSpecial)
					return false;
			}
		}
		return true;
	}

	EtlString Directory::GetUserDirectory()
	{
		static auto _GetUserDirectory = []() {
			struct passwd* pPwd = getpwuid(getuid());
			const char* homeDir = pPwd->pw_dir;
			EtlString retVal;
			MbCharArrayToEtlString(retVal, homeDir);
			return retVal;
		};
		static EtlString userDirectory = _GetUserDirectory();
		return userDirectory;
	}

	EtlString Directory::GetWorkingDirectory()
	{
		static auto _GetWorkingDirectory = []() {
			LocalCharPtr curDir(MAXPATHLEN);
			getcwd(curDir, MAXPATHLEN);
			EtlString retVal;
			MbCharArrayToEtlString(retVal, curDir);
			return retVal;
		};
		static EtlString workingDirectory = _GetWorkingDirectory();
		return workingDirectory;
	}

	EtlString Directory::GetExecutableDirectory()
	{
		static auto _GetExecutableDirectory = []() {
			uint32 dirLen = 0;
			_NSGetExecutablePath(nullptr, &dirLen);
			LocalCharPtr tempPath(dirLen);
			_NSGetExecutablePath(tempPath, &dirLen);
			EtlString retVal;
			MbCharArrayToEtlString(retVal, tempPath);
			size_t lastDir = retVal.find_last_of(ETL_TEXT('/'));
			retVal = retVal.substr(0, lastDir);
			return retVal;
		};
		static EtlString executableDirectory = _GetExecutableDirectory();
		return executableDirectory;
		// TODO: readlink /proc/self/exe for Linux
	}

	EtlString Directory::GetLocalAppDataDirectory()
	{
		static EtlString localAppDataDirectory = GetUserDirectory() + ETL_TEXT("/Application Support");
		return localAppDataDirectory;
	}

	EtlString Directory::GetDocumentsDirectory()
	{
		static EtlString documentsDirectory = GetUserDirectory() + ETL_TEXT("/Documents");
		return documentsDirectory;
	}

	EtlString Directory::GetDesktopDirectory()
	{
		static EtlString desktopDirectory = GetUserDirectory() + ETL_TEXT("/Desktop");
		return desktopDirectory;
	}

	std::vector<EtlString> Directory::ListFilesOrDirectories(const EtlString &dirName, uint8 findFlags, bool bIncludeSpecialDirs)
	{
		std::vector<EtlString> retVal;

		EtlString dir;
		if (dirName.back() == ETL_TEXT('*'))
			dir = RemoveLastElement(dirName);
		else
			dir = dirName;

		LocalCharPtr searchDir(dir);
		DIR* pSearch;
		struct dirent* pFindResult;
		struct stat dirStat;
		MbString thisDir(".");
		MbString prevDir("..");
		MbString dsStore(".DS_Store");

		if ((pSearch = opendir(searchDir)))
		{
			MbString dirString(searchDir);
			dirString += '/';
			EtlString retString;
			while ((pFindResult = readdir(pSearch)))
			{
				char* resName = pFindResult->d_name;
				bool bIsSpecial = (thisDir == resName) || (prevDir == resName) || (dsStore == resName);
				if (bIncludeSpecialDirs || !bIsSpecial)
				{
					MbString fullPath = dirString + resName;
					stat(fullPath.c_str(), &dirStat);
					switch (findFlags)
					{
					case 1: // Directories only
						if (dirStat.st_mode & S_IFDIR)
						{
							MbCharArrayToEtlString(retString, resName);
							retVal.push_back(retString);
						}
						break;
					case 2:
						if (!(dirStat.st_mode & S_IFDIR))
						{
							MbCharArrayToEtlString(retString, resName);
							retVal.push_back(retString);
						}
						break;
					case 3:
						MbCharArrayToEtlString(retString, resName);
						retVal.push_back(retString);
						break;
					}
				}
			}
		}

		return retVal;
	}

	void Directory::_RemoveDirectory(const EtlString &dirName)
	{
		LocalCharPtr dirNameMb(dirName);
		rmdir(dirNameMb);
	}
}
}

#endif // ETL_POSIX