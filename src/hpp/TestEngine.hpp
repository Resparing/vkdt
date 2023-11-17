//Header Guard
#pragma once

//Include Headers
#include <vkdt/debug.h>
#include <vkdt/device.h>
#include <vkdt/GPU.h>
#include <vkdt/instance.h>
#include <vkdt/queue.h>
#include <vkdt/surface.h>
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
		vkdt::debug::messenger* vkdtDebugMessenger;
		vkdt::GPU::GPU* vkdtGPU;
		vkdt::instance::instance* vkdtInstance;
		vkdt::queue::queue* vkdtGraphicsQueue;
		vkdt::surface::surface* vkdtSurface;
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