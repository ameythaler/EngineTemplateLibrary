#pragma once

#include "Utility/Types.h"

namespace ETL
{
namespace Filesystem
{
	class Directory
	{
	public:
		static bool FileExists(const EtlString& filename);
		static void RemoveFile(const EtlString& filename);
		static void RenameFileOrDirectory(const EtlString& oldName, const EtlString& newName);
		static bool DirectoryExists(const EtlString& dirName);
		static void Create_Directory(const EtlString& dirName);
		static void Remove_Directory(const EtlString& dirName);

		static void Move_File(const EtlString& fileName, const EtlString& parentDir);
		static void Move_Directory(const EtlString& dirName, const EtlString& parentDir);

		static std::vector<EtlString> ListDirectories(const EtlString& dirName, bool bIncludeSpecialDirs = false);
		static std::vector<EtlString> ListFiles(const EtlString& dirName);
		static std::vector<EtlString> ListFilesAndDirectories(const EtlString& dirName, bool bIncludeSpecialDirs = false);
		static bool IsDirectoryEmpty(const EtlString& dirName);

		static EtlString Parse(const EtlString& path);
		static EtlString ConcatPath(const EtlString& lhs, const EtlString& rhs);
		static EtlString GetLastElement(const EtlString& path);
		static EtlString RemoveLastElement(const EtlString& path);
		static EtlString GetExtension(const EtlString& filename);
		static EtlString GetFilename(const EtlString& fullPath);
		static EtlString Relative(const EtlString& path);
		static EtlString RelativeTo(const EtlString& path, const EtlString& base);
		static bool IsFullPath(const EtlString& path);

		static EtlString GetUserDirectory();
		static EtlString GetWorkingDirectory();
		static EtlString GetExecutableDirectory();
		static EtlString GetLocalAppDataDirectory();
		static EtlString GetDocumentsDirectory();
		static EtlString GetDesktopDirectory();

	private:
		static const uint8 s_kDirectories = 1;
		static const uint8 s_kFiles = 2;
		static const EtlChar s_kDivider;

		static std::vector<EtlString> ListFilesOrDirectories(const EtlString& dirName, uint8 findFlags, bool bIncludeSpecialDirs);
		static void _RemoveDirectory(const EtlString& dirName);
	};
}
}