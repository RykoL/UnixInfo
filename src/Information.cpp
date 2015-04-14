#include "../include/Information.h"

namespace System
{
	Information::Information()
	{
		getSystemInfo();
	}

	std::string Information::getUserName()
	{
		return std::string(getlogin());
	}

	std::string Information::getExecutionPath()
	{
		//get the pid for the current process
		int pid = getpid();

		//generate the path for accessing the exe symbolic link
		std::stringstream path;
		path << "/proc/" << std::to_string(pid) << "/exe";

		char *buffer = new char[512]; //allocating memory for the size of the symbolic link

		if( readlink(path.str().c_str(), buffer, 512) == -1) //reading the symbolic link /proc/PID/exe 
		{
			delete [] buffer;
			throw std::runtime_error("Information::getExecutionPath failed with error code: " + std::to_string(errno));
		}
		
		std::string symPath{buffer};

		delete [] buffer;
		return symPath;
	}

	void Information::getSystemInfo()
	{
		struct utsname info;

		if(uname(&info) != 0)
		{
			throw std::runtime_error("Information::getSystemInfo failed with error code: " + std::to_string(errno));
		}
		else
		{
			mSystemName = info.sysname;
			mVersion = info.version;
			mRelease = info.release;
			mMachine = info.machine;
		}
	}

	bool Information::isRoot()
	{
		return (getuid() == 0 && geteuid() == 0) ? true : false;
	}

	std::string Information::getEnvironmentVariable(const std::string &var)
	{
		return std::string{getenv(var.c_str())};
	}
}