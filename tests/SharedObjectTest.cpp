#include "../include/Process.h"
#include <iostream>
#include <cassert>

int main(int argc, char const *argv[])
{
	int pid = getpid();

	System::Process proc(pid);
	std::vector<std::string> x = proc.getLoadedObjects();

	std::cout<< x.size() << std::endl;

	assert(x.size() > 0);

	for(auto s : x)
	{
		std::cout<< s << std::endl;
	}

	return 0;
}