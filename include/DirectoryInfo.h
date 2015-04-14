#ifndef DIRECTORY_INFO_H
#define DIRECTORY_INFO_H

#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include <ctime>
#include <sstream>
#include <string>

namespace System
{

namespace IO
{
	class DirectoryInfo
	{

	public:
		DirectoryInfo(const std::string &path);
		~DirectoryInfo();

		bool open(const std::string &path);
		std::vector<std::unique_ptr<DirectoryInfo>> getDirectories();
		std::string getLastAccessTime() {return ConvertToTimeString(mAccessTime);};
		std::string getLastModifiedTime() {return ConvertToTimeString(mModificationTime);};
		std::string getStatusChangedTime() {return ConvertToTimeString(mStatusChangeTime);};

	private:
		void getDirectoryInfo();
		std::string ConvertToTimeString(time_t t);

	private:
		std::string mPath;

		DIR *mDirectoryPointer;
		int mFileDescriptor{-1};
		time_t mAccessTime;
		time_t mModificationTime;
		time_t mStatusChangeTime;

	};
}
}

#endif