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
		void stopVKDTFrame(void);

	private:

		//Vulkan Memory Allocator
		VkAllocationCallbacks* pAllocator;

		//Vector of Vulkan Semaphores
		std::vector<VkSemaphore> vkdtVKImageAvailableSemaphores;
		std::vector<VkSemaphore> vkdtVKRenderFinishedSemaphores;

		//Vector of Vulkan Fences
		std::vector<VkFence> vkdtVKInFlightFences;

		//Maximum Number of Vulkan Frames in Flight
		const int32_t MAX_FRAMES = 2;

	protected:

		//Debugging Variables
		bool debug{};
		bool verbose{};

	};
}