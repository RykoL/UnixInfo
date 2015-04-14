#include <iostream>
#include <unistd.h>
#include "include/Information.h"
#include "include/DirectoryInfo.h"

int main(int argc, char* argv[])
{
	System::Information info;
	std::cout<< info.getSystemName() << " " << info.getRelease() << " " << info.getMachine() << std::endl;
	std::cout<< info.getExecutionPath() << std::endl;
	std::cout<< info.getLanguage() << std::endl;

	System::IO::DirectoryInfo dInfo("/home/rico");
	std::cout<< dInfo.getLastAccessTime() << "\n" << dInfo.getLastModifiedTime() << "\n" << dInfo.getStatusChangedTime() << std::endl;;

	return 0;
}