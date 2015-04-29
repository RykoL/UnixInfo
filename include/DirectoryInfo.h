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
#include <cstring>
#include <sstream>
#include <string>
#include <iostream>

namespace System
{

namespace IO
{
	enum Permission{
		User_Read = S_IRUSR,
		User_Write = S_IWUSR,
		User_Execute = S_IXUSR,
		Group_Read = S_IRGRP,
		Group_Write = S_IWGRP,
		Group_Execute = S_IXGRP,
		Other_Read = S_IROTH,
		Other_Write = S_IWOTH,
		Other_Execute = S_IXOTH
	};

	class DirectoryInfo
	{

	public:
		DirectoryInfo(const std::string &path);
		DirectoryInfo() {};
		~DirectoryInfo();

		bool open(const std::string &path);
		std::unique_ptr<DirectoryInfo> create(const std::string &path, Permission pm);
		void deleteDir();
		void deleteDir(const std::string &path);
		void close();

		std::vector<std::unique_ptr<DirectoryInfo>> getDirectories();
		std::vector<std::string> getFileNames();
		std::string getFullPath() {return mPath;};
		std::string getLastAccessTime() {return ConvertToTimeString(mAccessTime);};
		std::string getLastModifiedTime() {return ConvertToTimeString(mModificationTime);};
		std::string getStatusChangedTime() {return ConvertToTimeString(mStatusChangeTime);};

		static bool Exists(const std::string &path);

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
		mode_t mPermission;
	};
}
}

#endif