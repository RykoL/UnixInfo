#include "../include/ProcessInformation.h"

System::ProcessInformation::ProcessInformation(unsigned int pid) : mPid{pid}
{

}

System::ProcessInformation::ProcessInformation() 
{
	
}

//Description: Spawns a process without any arguments
void System::ProcessInformation::start(const std::string &path)
{
	pid_t pid;

	if((pid = fork()) < 0)
	{
		throw std::runtime_error("ProcessInformation::start failed with following error. " + std::string{std::strerror(errno)});
	}

	else if(pid == 0)
	{
		if(execl(path.c_str(),"") < 0)
		{
			throw std::runtime_error("ProcessInformation::start failed with following error. " + std::string{std::strerror(errno)});
		}
	}
}

//Description: Spawns a process with specified arguments
void System::ProcessInformation::start(const std::string &path,const std::initializer_list<std::string> &args)
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
		throw std::runtime_error("ProcessInformation::start failed with following error. " + std::string{std::strerror(errno)});
	}

	//if the process has pid == 0 it knows it's the copied process(the child process)
	//in this case we call exec to overwrite the current process with the code from the specified file and start at it's main function
	else if(pid == 0)
	{
		//we use the execv function instead of the execl function to pass our argument array
		if(execv(path.c_str(), arguments) < 0)
		{
			throw std::runtime_error("ProcessInformation::start failed with following error. " + std::string{std::strerror(errno)});
		}
	}
}

void System::ProcessInformation::stop()
{
	if(kill(mPid, SIGTERM) != 0)
	{
		throw std::runtime_error("ProcessInformation::kill failed with following error. " + std::string{std::strerror(errno)});
	}
}

void System::ProcessInformation::pause()
{
	if(kill(mPid, SIGSTOP) != 0)
	{
		throw std::runtime_error("ProcessInformation::pause failed with following error. " + std::string{std::strerror(errno)});
	}
}

void System::ProcessInformation::resume()
{
	if(kill(mPid, SIGCONT) != 0)
	{
		throw std::runtime_error("ProcessInformation::pause failed with following error. " + std::string{std::strerror(errno)});
	}
}