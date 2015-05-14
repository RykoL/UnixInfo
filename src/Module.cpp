#include "../include/Module.h"

namespace System
{
	Module::Module()
	{

	}

	Module::~Module()
	{

	}

	//Function to load a LKM(Loadable kernel module) into the kernel
	void Module::load(const std::string &path,const std::string &param)
	{
		//root privileges are required for loading/unloading a module
		if(Information::isRoot())
		{

			int fd;

			if((fd = open(path,O_RDONLY)) == -1)
			{
				throw std::runtime_error("failed to obtrain file descriptor. " + std::string{std::strerror(errno)});  
			}

			if(syscall(SYS_finit_module,fd,param.c_str(),0))
			{
				throw std::runtime_error("Module::load failed with following error: " + std::string{std::strerror(errno)});
			}
		}
	}

	void Module::unload(const std::string &name)
	{
		if(Information::isRoot())
		{
			if(syscall(SYS_delete_module,name.c_str(),O_NONBLOCK) == -1)
			{
				throw std::runtime_error("Module::unload failed with following error: " + std::string{std::strerror(errno)});
			}
		}
	}
}