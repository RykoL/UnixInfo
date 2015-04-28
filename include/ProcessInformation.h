#ifndef PROCESS_INFORMATION_H
#define PROCESS_INFORMATION_H

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdexcept>
#include <errno.h>
#include <string>
#include <cstring>
#include <initializer_list>
#include <iostream>

namespace System
{
	class ProcessInformation
	{
	public:
		ProcessInformation(unsigned int pid);
		ProcessInformation();
		~ProcessInformation() {};
		
		static void start(const std::string &path);
		static void start(const std::string &path,const std::initializer_list<std::string> &args);
		void stop();
		void pause();
		void resume();

	private:
		unsigned int mPid;
	};
}



#endif