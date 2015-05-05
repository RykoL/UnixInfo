#ifndef PATH_H
#define PATH_H

#include <string>
#include <iostream>

namespace System
{

	namespace IO
	{

		namespace Path
		{
			inline std::string Combine(std::string path1,std::string path2)
			{
				if(path1.length() == 0 || path2.length() == 0)
				{
					return (path1.length() == 0) ? path2 : path1;
				}

				if(path1.back() == '/' && path2.front() == '/')
				{
					return path1 + path2.erase(0,1);
				}

				if(path1.back() == '/' && path2.front() != '/')
				{
					return path1 + path2;
				}

				return "";
			}
		}
	}

}

#endif