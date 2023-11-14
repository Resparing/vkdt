//Header Guard
#pragma once

//Include Headers
#include <vkdt/device.h>
#include <vkdt/GPU.h>
#include <vkdt/instance.h>
#include <vkdt/queue.h>
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
		vkdt::device::device* vkdtDevice;
		vkdt::GPU::GPU* vkdtGPU;
		vkdt::instance::instance* vkdtInstance;
		vkdt::queue::queue* vkdtGraphicsQueue;
		vkdt::window::window* vkdtWindow;

		//Debugging Variables
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