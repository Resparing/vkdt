//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace vkdt::frame
{
	class frame
	{
	public:

		/**
		 * @brief Initialize VKDT Frame
		 *
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		frame(const bool debug = false, const bool verbose = false) noexcept;

		~frame();

		/**
		 * @brief Setup VKDT Frame
		 * 
		 * @param allocator Vulkan Memory Allocator
		 */
		void setupVKDTFrame(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);

		/**
		 * @brief Draw VKDT Frame
		 */
		void drawVKDTFrame(void);

		/**
		 * @brief Stop Frame Execution
		 */
		void stopFrame(void);

	private:

		//Vulkan Memory Allocator
		VkAllocationCallbacks* pAllocator;

		//Vulkan Semaphores
		VkSemaphore vkdtVKImageAvailableSemaphore;
		VkSemaphore vkdtVKRenderFinishedSemaphore;

		//Vulkan Fence
		VkFence vkdtVKInFlightFence;

	protected:

		//Debugging Variables
		bool debug{};
		bool verbose{};

	};
}