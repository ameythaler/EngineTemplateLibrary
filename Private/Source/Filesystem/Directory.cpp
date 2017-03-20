#include "Filesystem/Directory.h"
#include "Math/Math.h"
#include <list>

using ETL::Math::Min;

namespace ETL
{
namespace Filesystem
{
	void Directory::Remove_Directory(const EtlString& dirName)
	{
		std::vector<EtlString> dirContents = ListFilesAndDirectories(dirName, true);
		const EtlString prevDir(ETL_TEXT(".."));
		const EtlString thisDir(ETL_TEXT("."));

		for (auto content : dirContents)
		{
			if (content == prevDir || content == thisDir)
				continue;
			EtlString contentPath = ConcatPath(dirName, content);
			if (DirectoryExists(contentPath))
				Remove_Directory(contentPath);
			else
				RemoveFile(contentPath);
		}

		_RemoveDirectory(dirName);
	}

	void Directory::Move_File(const EtlString& fileName, const EtlString& parentDir)
	{
		EtlString newName = ConcatPath(parentDir, GetLastElement(fileName));
		RenameFileOrDirectory(fileName, newName);
	}

	void Directory::Move_Directory(const EtlString& dirName, const EtlString& parentDir)
	{
		// Create the new directory
		EtlString newDir = ConcatPath(parentDir, GetLastElement(dirName));
		Create_Directory(newDir);

		// Move the files
		std::vector<EtlString> contents = ListFilesAndDirectories(dirName, false);
		for (auto content : contents)
		{
			EtlString contentPath = ConcatPath(dirName, content);
			if (DirectoryExists(contentPath))
				Move_Directory(contentPath, newDir);
			else
				Move_File(contentPath, newDir);
		}

		Remove_Directory(dirName);
	}

	std::vector<EtlString> Directory::ListDirectories(const EtlString& dirName, bool bIncludeSpecialDirs)
	{
		return ListFilesOrDirectories(dirName, s_kDirectories, bIncludeSpecialDirs);
	}

	std::vector<EtlString> Directory::ListFiles(const EtlString& dirName)
	{
		return ListFilesOrDirectories(dirName, s_kFiles, false);
	}

	std::vector<EtlString> Directory::ListFilesAndDirectories(const EtlString& dirName, bool bIncludeSpecialDirs)
	{
		return ListFilesOrDirectories(dirName, s_kDirectories | s_kFiles, bIncludeSpecialDirs);
	}

	EtlString Directory::Parse(const EtlString &path)
	{
		auto pathElems = path.split(ETL_TEXT("/\\"));
		EtlString retVal;
		if (!pathElems.empty())
		{
			if (pathElems[0] == ETL_TEXT("~"))
				retVal += GetUserDirectory();
			else
				retVal += pathElems[0];
			size_t elemCnt = pathElems.size();
			for (size_t elemIdx = 1; elemIdx < elemCnt; ++elemIdx)
			{
				retVal += s_kDivider + pathElems[elemIdx];
			}
		}
		return retVal;
	}

	EtlString Directory::ConcatPath(const EtlString &lhs, const EtlString &rhs)
	{
		if (lhs.empty() || lhs.back() == s_kDivider)
			return lhs + rhs;
		else
			return lhs + s_kDivider + rhs;
	}

	EtlString Directory::GetLastElement(const EtlString& path)
	{
		EtlString retVal = path;
		size_t lastElemIdx = path.find_last_of(s_kDivider);
		if (lastElemIdx != EtlString::npos)
		{
			retVal = path.substr(lastElemIdx + 1);
		}
		return retVal;
	}

	EtlString Directory::RemoveLastElement(const EtlString& path)
	{
		EtlString retVal;
		size_t lastElemIdx = path.find_last_of(s_kDivider);
		if (lastElemIdx != EtlString::npos)
			retVal = path.substr(0, lastElemIdx);
		return retVal;
	}

	EtlString Directory::GetExtension(const EtlString& filename)
	{
		size_t extIdx = filename.find_last_of(ETL_TEXT('.'));
		if (extIdx != EtlString::npos)
			return filename.substr(extIdx);
		else
			return EtlString();
	}

	EtlString Directory::GetFilename(const EtlString& fullPath)
	{
		EtlString filename = GetLastElement(fullPath);
		size_t extIdx = filename.find_last_of(ETL_TEXT('.'));
		if (extIdx != EtlString::npos)
			return filename.substr(0, extIdx);
		else
			return filename;
	}

	EtlString Directory::Relative(const EtlString& path)
	{
		return RelativeTo(path, GetWorkingDirectory());
	}

	EtlString Directory::RelativeTo(const EtlString& path, const EtlString& base)
	{
		if (path.size() < 2 || base.size() < 2)
			return path;
		if (path[0] != base[0])
			return path;

		std::vector<EtlString> pathElements = path.split(ETL_TEXT("/\\"));
		std::vector<EtlString> baseElements = base.split(ETL_TEXT("/\\"));
		size_t maxIdx = Min(pathElements.size(), baseElements.size());

		size_t maxMatchIdx = 0;
		for (size_t curIdx = 1; curIdx < maxIdx; ++curIdx)
		{
			if (pathElements[curIdx] == baseElements[curIdx])
				++maxMatchIdx;
			else
				break;
		}

		size_t backDiff = baseElements.size() - maxMatchIdx - 1;
		size_t fwdSize = pathElements.size();
		EtlString retVal;
		for (size_t backIdx = 0; backIdx < backDiff; ++backIdx)
			retVal = ConcatPath(retVal, ETL_TEXT(".."));
		for (size_t fwdIdx = maxMatchIdx + 1; fwdIdx < fwdSize; ++fwdIdx)
			retVal = ConcatPath(retVal, pathElements[fwdIdx]);

		return retVal;
	}

	bool Directory::IsFullPath(const EtlString& path)
	{
		if (path.size() > 1 && path[1] == ETL_TEXT(':'))
			return true;
		else
			return false;
	}
}
}