#include "../include/Process.h"

namespace System
{
	Process::Process(int pid)
	{
		mReader.open("/proc/" + std::to_string(pid) + "/stat");

		if(!mReader.is_open())
		{
			throw std::runtime_error("Process::Process failed to open file");
		}

		readData();
	}

	//TODO: add remaining variables
	Process::Process(const Process &proc)
	{
		mData = proc.mData;
		mPid = proc.mPid;

		mProcessName = proc.mProcessName;
		mState = proc.mState;
	}


	Process::~Process()
	{
		mReader.close();
	}



	//were basically reading from /proc/[pid]/stat
	void Process::readData()
	{
		std::getline(mReader,mData);

		char pName[512];
		char state;
		//std::sscanf from the c library comes handy here, because we dont have to deal with file parsing
		std::sscanf(mData.c_str(), "%d %s %c", &mPid, pName, &state);

		mProcessName = pName;
		mExecutionPath = getExPath();
		mState = charToState(state);
	}

	//function to retrieve the full execution path of the process binary
	std::string Process::getExPath()
	{
		std::string path = "/proc/" + std::to_string(mPid) + "/exe";

		//still looking for a way to dynamically get the required buffer size
		//for the symlink, stat wont help here.
		char * buffer = new char[PATH_MAX];

		if(readlink(path.c_str(), buffer, PATH_MAX) == -1)
		{
			delete [] buffer;
			throw std::runtime_error("Process::getExPath failed with following error: " + std::string{std::strerror(errno)});
		}

		std::string exPath{buffer};

		delete [] buffer;
		return exPath;
	}

	void Process::getCmd()
	{
		mReader.open("/proc/" + std::to_string(mPid) + "/cmdline");

		if(!mReader.is_open())
		{
			throw std::runtime_error("Process::getCmd: could not open file");
		}

		std::getline(mReader,mCommandLine);
	}

	Process::State Process::charToState(char c)
	{
		switch(c)
		{
			case 'R':
				return State::Running;
				break;
			case 'S':
				return State::Sleeping;
				break;
			case 'D':
				return State::DiskSleep;
				break;
			case 'T':
				return State::Stopped;
				break;
			case 'W':
				return State::Paging;
				break;
		}

		return State::Stopped;
	}



	void System::Process::stop()
	{
		if(kill(mPid, SIGTERM) != 0)
		{
			throw std::runtime_error("Process::stop failed with following error. " + std::string{std::strerror(errno)});
		}
	}



	void System::Process::pause()
	{
		if(kill(mPid, SIGSTOP) != 0)
		{
			throw std::runtime_error("Process::pause failed with following error. " + std::string{std::strerror(errno)});
		}
	}



	void System::Process::resume()
	{
		if(kill(mPid, SIGCONT) != 0)
		{
			throw std::runtime_error("Process::resume failed with following error. " + std::string{std::strerror(errno)});
		}
	}



	//if we wanna start a process without parameters
	void System::Process::start(const std::string &path)
	{
		pid_t pid;

		if((pid = fork()) < 0)
		{
			throw std::runtime_error("Process::start failed with following error. " + std::string{std::strerror(errno)});
		}

		else if(pid == 0)
		{
			if(execl(path.c_str(),"") < 0)
			{
				throw std::runtime_error("Process::start failed with following error. " + std::string{std::strerror(errno)});
			}
		}
	}



	//Description: Spawns a process with specified arguments
	void System::Process::start(const std::string &path,const std::initializer_list<std::string> &args)
	{
		int argc = args.size();
		//we need the +2 because arguments[0] is reserved for the file name and we need a
		//terminating null string at the end of the array
		char * arguments[argc + 2]; //create a array with the size of the argument count
	
		std::initializer_list<std::string>::iterator it;

		//retrieve the filename for argv[0]
		std::string filename = "." + path.substr(path.find_last_of("/"), path.size());
		arguments[0] = const_cast<char*>(filename.c_str());

		//transfer the arguments from the initializer_list to the argument array
		//im using the initializer_list here, because its way easier to implement than variadic temlate arguments
		//we need to start from 1, because the parameter at pos 0 is reserved for the file name
		int i = 1;
		for(it = args.begin(); it != args.end(); ++it, i++)
		{
			arguments[i] = const_cast<char*>((*it).c_str()); //i hate c-style, needed to get rid of the const char*
		}

		//we have to set the last string to a terminating null character to show that no other argument is coming after this
		arguments[argc + 1] = '\0';

		pid_t pid;

		//we create a copy of our own process
		if((pid = fork()) < 0)
		{
			throw std::runtime_error("Process::start failed with following error. " + std::string{std::strerror(errno)});
		}

		//if the process has pid == 0 it knows it's the copied process(the child process)
		//in this case we call exec to overwrite the current process with the code from the specified file and start at it's main function
		else if(pid == 0)
		{
			//we use the execv function instead of the execl function to pass our argument array
			if(execv(path.c_str(), arguments) < 0)
			{
				throw std::runtime_error("Process::start failed with following error. " + std::string{std::strerror(errno)});
			}
		}
	}
}