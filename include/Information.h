#ifndef INFORMATION_H
#define INFORMATION_H

#include <unistd.h>
#include <sys/utsname.h> //required for uname(2)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h> //needed for errno
#include <stdexcept> //needed for std::logic_error
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

namespace System 
{

class Information
{
public:
	Information();

	std::string getUserName();
	std::string getExecutionPath();

	std::string getSystemName() const noexcept {return mSystemName;};
	std::string getVersion() const noexcept {return mVersion;};
	std::string getRelease() const noexcept {return mRelease;};
	std::string getMachine() const noexcept {return mMachine;};
	std::string getEnvironmentVariable(const std::string &var);
	std::string getLanguage() {return getEnvironmentVariable("LANG");};

	static bool isRoot();
private:
	void getSystemInfo();

private:
	std::string mSystemName;
	std::string mVersion;
	std::string mRelease;
	std::string mMachine;

};

}

#endif