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
			throw std::runtime_error("can't obtain file descriptor, failed with error code: " + std::string{std::strerror(errno)});
		}

		getDirectoryInfo();
	}

	DirectoryInfo::~DirectoryInfo()
	{
		closedir(mDirectoryPointer);
	}

	void DirectoryInfo::getDirectoryInfo()
	{
		struct stat dStat;

		if(fstat(mFileDescriptor, &dStat) != 0)
		{
			throw std::runtime_error("DirectoryInfo::getDirectoryInfo failed with error code: " + std::string{std::strerror(errno)});
		}

		mAccessTime = dStat.st_atime;
		mModificationTime = dStat.st_mtime;
		mStatusChangeTime = dStat.st_ctime;
		mPermission = dStat.st_mode;
	}	

	bool DirectoryInfo::open(const std::string &path)
	{
		if( (mDirectoryPointer = opendir(path.c_str())) == nullptr )
		{
			return false;
		}

		return true;
	}

	void DirectoryInfo::close()
	{
		mPath = "";
		mFileDescriptor = -1;
		mAccessTime = 0;
		mModificationTime = 0;
		mStatusChangeTime = 0;

		closedir(mDirectoryPointer);
	}

	std::unique_ptr<DirectoryInfo> DirectoryInfo::create(const std::string &path,Permission pm)
	{
		umask(0);

		if (mkdir(path.c_str(), pm) == -1)
		{
			throw std::runtime_error("DirectoryInfo::createDirectory failed with error code: " + std::string{std::strerror(errno)});
		}

		return std::unique_ptr<DirectoryInfo>(new DirectoryInfo(path));
	}

	void DirectoryInfo::deleteDir()
	{
		if(access(mPath.c_str(), F_OK))
		{
			if(!rmdir(mPath.c_str()))
			{
				throw std::runtime_error("DirectoryInfo::deleteDirectory failed with error code: " + std::string{std::strerror(errno)});
			}


		}
		else
		{
			std::cerr<< "No acces to the file " << mPath << std::endl;
		}
	}

	void DirectoryInfo::deleteDir(const std::string &path)
	{
		if(access(path.c_str(), F_OK))
		{
			if(!rmdir(path.c_str()))
			{
				throw std::runtime_error("DirectoryInfo::deleteDirectory failed with error code: " + std::string{std::strerror(errno)});
			}
		}

		else
		{
			std::cerr << "No accss to the file " << path << std::endl;
		}
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

	std::vector<std::string> DirectoryInfo::getFileNames()
	{
		std::vector<std::string> FileNames;

		dirent *dirp;

		while((dirp = readdir(mDirectoryPointer)) != nullptr)
		{
			if(dirp->d_type == DT_REG)
			{
				FileNames.push_back(dirp->d_name);
			}
		}

		return FileNames;
	}

	std::string DirectoryInfo::ConvertToTimeString(time_t t)
	{
		std::tm *tm = std::localtime(&t);

		std::stringstream ss;
		ss << tm->tm_mday << "-" << tm->tm_mon + 1<< "-" << tm->tm_year + 1900 << " " << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;

		return ss.str();
	}

	bool DirectoryInfo::Exists(const std::string &path)
	{
		DIR *dir;

		if((dir = opendir(path.c_str())) != nullptr)
		{
			closedir(dir);
			return true;
		}

		return false;
	}
}

}