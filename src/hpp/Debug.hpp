//Header Guard
#pragma once

//Include Headers
#include <cstddef>
#include <cstdint>

namespace Debug
{
	//Clear Terminal Window
	void clear(void);

	//Check if Debugging
	bool isDebug(const size_t argc, const char* argv[]);

	//Exit Program Depending if Debugging or not
	int EXIT_CODE(const bool debug, const size_t argc, const char* argv[]);
}