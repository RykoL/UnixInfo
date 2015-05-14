#ifndef MODULE_H
#define MODULE_H

#include "Process.h"
#include "Information.h"
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

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
} 

#endif