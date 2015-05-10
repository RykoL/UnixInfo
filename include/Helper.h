#ifndef HELPER_H
#define HELPER_H

#include <ctime>
#include <sstream>
#include <string>

namespace System
{

	//TODO: rewrite the function
	inline std::string TimeToString(time_t t)
	{
		std::tm *tm = std::localtime(&t);

		std::stringstream ss;
		ss << tm->tm_mday << "-" << tm->tm_mon + 1<< "-" << tm->tm_year + 1900 << " " << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;

		return ss.str();
	}
}

#endif