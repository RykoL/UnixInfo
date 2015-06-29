#ifndef MODULE_H
#define MODULE_H

#include "Process.h"
#include "Information.h"
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <vector>

namespace System
{
	class Module
	{
	public:
		Module();
		~Module();
		void load(const std::string &path,const std::string &param);
		void unload(const std::string &name);

	private:
		std::string mModName;
	};

	inline std::vector<std::string> listModules()
	{
		std::ifstream mod;
		std::string modName;
		std::string modLine;
		std::vector<std::string> vec;

		mod.open("/proc/modules");

		if(mod.is_open())
		{
			while(std::getline(mod,modLine))
			{
				size_t found = modLine.find_first_of(" ");
				modName = modLine.substr(0,found);
				vec.push_back(modName);
			}
		}

		else
			std::cout<< "Couldn't open /proc/modules" << std::endl;
		return vec;
	}
} 

#endif