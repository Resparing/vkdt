//Include Header File
#include "../Debug.hpp"

//Include Headers
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <stdexcept>

void Debug::clear(void)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)  //Windows
		system("cls");
#else  //Unix
		system("clear");
#endif
}

bool Debug::isDebug(const size_t argc, const char* argv[])
{
	//Check if Argument Count is Greater than 2 - Exec Path and DEBUG Argument
	bool argcGreaterThan2 = argc >= 2;

	if(argcGreaterThan2 == false)
	{
		//Argument Count is 1
		return false;
	}

	//Check if Second Argument is "DEBUG"
	bool isDebug = strcmp("DEBUG", argv[1]) == 0;

	if(isDebug)
	{
		//Warn that Debugging is On
		std::cout << "Debugging is On!\n";
	}

	return isDebug;
}

int Debug::EXIT_CODE(const bool debug, const size_t argc, const char* argv[])
{
	if(!debug)
	{
		return EXIT_SUCCESS;
	}

	//Debugging
	std::cout << "Number of Arguments (" << argc << "):\n";

	for(size_t i{}; i < argc; ++i)
	{
		std::cout << "\t\"" << argv[i] << "\"\n";
	}

	std::cout << "Press Enter to Terminate...\n";
	std::cin.get();

	return EXIT_SUCCESS;
}