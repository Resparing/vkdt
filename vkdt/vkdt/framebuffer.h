//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace vkdt::framebuffer
{
	class framebuffer
	{
	public:

		/**
		 * @brief Initialized VKDT Frame Buffer
		 *
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		framebuffer(const bool debug = false, const bool verbose = false) noexcept;

		~framebuffer();

		/**
		 * @brief Create VKDT Frame Buffer
		 *
		 * @param allocator Vulkan Memory Allocator
		 */
		void createVKDTFramebuffer(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);

	private:

		//Vulkan Memory Allocator
		VkAllocationCallbacks* pAllocator;

	protected:

		//Vector of Vulkan Frame Buffers
		std::vector<VkFramebuffer> vkdtVKFrameBuffers;

		//Debugging Variables
		bool debug{};
		bool verbose{};

	};
}