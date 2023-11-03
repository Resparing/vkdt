//Header Guard
#pragma once

//Include Headers
#include <vkdt/GPU.h>
#include <vkdt/instance.h>
#include <vkdt/window.h>

namespace TestEngine
{
	class TestEngine
	{
	public:

		TestEngine(const bool debug, const bool verbose);
		~TestEngine();

	private:

		/* VKDT Parameters */
		vkdt::instance::instance* vkdtInstance;
		vkdt::window::window* vkdtWindow;
		vkdt::GPU::GPU* vkdtGPU;

		//Debugging and Verbose Variables
		bool isDebug{};
		bool isVerbose{};

	protected:

		//Create Window
		void createWindow(void);

		//Initialize VKDT
		void vkdtInit(void);

		//Main Loop Function
		void mainLoop(void);

	};
}