#include <iostream>
#include <unistd.h>
#include "include/Information.h"
#include "include/DirectoryInfo.h"
#include "include/Path.h"
#include "include/ProcessInformation.h"

int main(int argc, char* argv[])
{
	System::Information info;
	std::cout<< info.getSystemName() << " " << info.getRelease() << " " << info.getMachine() << std::endl;
	std::cout<< info.getExecutionPath() << std::endl;
	std::cout<< info.getLanguage() << std::endl;

	System::IO::DirectoryInfo dInfo("/home/rico/Programmieren");
	//dInfo.create("test", static_cast<System::IO::Permission>(System::IO::Permission::User_Read | System::IO::Permission::Group_Read /*| System::IO::Permission::User_Write*/));
	//dInfo.deleteDir();
	std::cout<< dInfo.getLastAccessTime() << "\n" << dInfo.getLastModifiedTime() << "\n" << dInfo.getStatusChangedTime() << std::endl;
	/*
	unsigned int pid;
	std::cin >> pid;

	System::ProcessInformation pInfo{pid};
	*/

	System::ProcessInformation::start("/home/rico/Programmieren/C++/system/tests/args", {"hudelblub","turen frass", "Bohse", "Paulaner"});
	return 0;
}