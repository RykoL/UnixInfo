#include "../include/DirectoryInfo.h"

namespace System
{

namespace IO
{
	DirectoryInfo::DirectoryInfo(const std::string &path)
	{
		if(!open(path))
		{
			throw std::runtime_error("can't open directory " + path);
		}

		mPath = path;
		
		if((mFileDescriptor = dirfd(mDirectoryPointer)) == -1)
		{
			throw std::runtime_error("can't obtain file descriptor, failed with error code: " + std::to_string(errno));
		}

		getDirectoryInfo();
	}

	void DirectoryInfo::getDirectoryInfo()
	{
		struct stat dStat;

		if(fstat(mFileDescriptor, &dStat) != 0)
		{
			throw std::runtime_error("DirectoryInfo::getDirectoryInfo failed with error code: " + std::to_string(errno));
		}

		mAccessTime = dStat.st_atime;
		mModificationTime = dStat.st_mtime;
		mStatusChangeTime = dStat.st_ctime;
	}

	DirectoryInfo::~DirectoryInfo()
	{
		closedir(mDirectoryPointer);
	}

	bool DirectoryInfo::open(const std::string &path)
	{
		if( (mDirectoryPointer = opendir(path.c_str())) == nullptr )
		{
			return false;
		}

		return true;
	}

	std::vector<std::unique_ptr<DirectoryInfo>> DirectoryInfo::getDirectories()
	{
		std::vector<std::unique_ptr<DirectoryInfo>> dirs;

		struct dirent *dirp;

		while((dirp = readdir(mDirectoryPointer)) != nullptr)
		{
			std::string dName{dirp->d_name};

			if(dirp->d_type == DT_DIR && dName != ".." && dName != ".")
				dirs.emplace_back(std::unique_ptr<DirectoryInfo>{new DirectoryInfo(mPath + "/" + dName)});
		}

		return dirs;
	}

	std::string DirectoryInfo::ConvertToTimeString(time_t t)
	{
		std::tm *tm = std::localtime(&t);

		std::stringstream ss;
		ss << tm->tm_mday << "-" << tm->tm_mon + 1<< "-" << tm->tm_year + 1900 << " " << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;

		return ss.str();
	}
}

}