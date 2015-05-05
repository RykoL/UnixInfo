#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <fstream>
#include <stdexcept>
#include <cstdio>
#include "Path.h"

namespace System
{
	class Process
	{
	public:
		Process(int pid);
		~Process();
		
		static void start(const std::string &path);
		static void start(const std::string &path,const std::initializer_list<std::string> &args);
		
		void stop();
		void pause();
		void resume();
	public:
		enum State
		{
			Running,
			Sleeping,
			DiskSleep,
			Stopped,
			Paging
		};

	private:
		void readData();
		State charToState(char c);

	private:
		std::ifstream mReader;
		std::string mData;

		int mPid;
		int mProcessGroup;
		int tty;

		std::string mProcessName;
		State mState;
		

	};
}

#endif
