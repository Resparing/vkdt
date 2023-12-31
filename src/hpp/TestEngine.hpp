//Header Guard
#pragma once

//Include Headers
#include <vkdt/commandbuffer.h>
#include <vkdt/debug.h>
#include <vkdt/device.h>
#include <vkdt/frame.h>
#include <vkdt/framebuffer.h>
#include <vkdt/GPU.h>
#include <vkdt/imageview.h>
#include <vkdt/instance.h>
#include <vkdt/pipeline.h>
#include <vkdt/queue.h>
#include <vkdt/surface.h>
#include <vkdt/swapchain.h>
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
		vkdt::commandbuffer::commandbuffer* vkdtCommandBuffer;
		vkdt::device::device* vkdtDevice;
		vkdt::debug::messenger* vkdtDebugMessenger;
		vkdt::frame::frame* vkdtFrame;
		vkdt::framebuffer::framebuffer* vkdtFrameBuffer;
		vkdt::GPU::GPU* vkdtGPU;
		vkdt::instance::instance* vkdtInstance;
		vkdt::imageview::imageview* vkdtImageView;
		vkdt::pipeline::pipeline* vkdtPipeline;
		vkdt::queue::queue* vkdtQueue;
		vkdt::surface::surface* vkdtSurface;
		vkdt::swapchain::swapchain* vkdtSwapchain;
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