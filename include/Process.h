#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <linux/limits.h>
#include <errno.h>
#include <cstring>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstdio>
#include <initializer_list>
#include <iostream>

namespace System
{
	class Process
	{
	public:
		enum State
		{
			Running,
			Sleeping,
			DiskSleep,
			Stopped,
			Paging
		};

	public:
		Process(int pid);
		Process(const Process& proc);
		~Process();
		
		static void start(const std::string &path);
		static void start(const std::string &path,const std::initializer_list<std::string> &args);

		void stop();
		void pause();
		void resume();

		std::string getProcessName() const noexcept { return mProcessName;};
		std::string getExecutionPath() const noexcept { return mExecutionPath;};
		std::string getCommandLine() const noexcept {return mCommandLine;};

		int getPid() const noexcept {return mPid;};
		State getState() const noexcept {return mState;};
		

	private:
		void readData();
		State charToState(char c);
		std::string getExPath();
		void getCmd();

	private:
		std::ifstream mReader;
		std::string mData;

		int mPid;

		std::string mProcessName;
		std::string mExecutionPath;
		std::string mCommandLine;
		State mState;
		

	};
}

#endif
