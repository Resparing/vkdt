//Include Headers
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>

//Include Debugging Header File
#include "../hpp/Debug.hpp"

//Include Test Engine
#include "../hpp/TestEngine.hpp"

/* Main Method */
int main(int argc, const char* argv[])
{
	//Clear Terminal Window
	Debug::clear();

	//Check if Debugging
	bool debug = Debug::isDebug(static_cast<size_t>(argc), argv);

	//Try Runnning Test Engine
	try
	{
		TestEngine::TestEngine* engine = new TestEngine::TestEngine(debug, debug);

		delete engine;
	}
	catch(const std::exception& exception)
	{
		std::cerr << "[ERROR] " << exception.what() << '\n';

		std::terminate();
	}

	return Debug::EXIT_CODE(debug, static_cast<size_t>(argc), argv);
}