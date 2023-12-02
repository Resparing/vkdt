//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace vkdt::commandbuffer
{
	class commandbuffer
	{
	public:

		/**
		 * @brief Initialize VKDT Command Buffer
		 *
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		commandbuffer(const bool debug = false, const bool verbose = false) noexcept;

		~commandbuffer();

		/**
		 * @brief Create VKDT Command Buffer
		 *
		 * @param allocator Vulkan Memory Allocator
		 */
		void createVKDTCommandbuffer(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);

		/**
		 * @brief Record VKDT Command Buffer
		 *
		 * @param commandBuffer Buffer to Write Commands to
		 * @param index Index of Swapchain Image to Write to

		 * @attention Only used for Internal Purposes
		 */
		static void recordVKCommandBuffer(const VkCommandBuffer& commandBuffer = VK_NULL_HANDLE, const uint32_t index = 0);

	private:

		//Vulkan Memory Allocator
		VkAllocationCallbacks* pAllocator;

		//Vulkan Command Pool
		VkCommandPool vkdtVKCommandPool;

	protected:

		//Vulkan Command Buffer
		VkCommandBuffer vkdtVKCommandBuffer;

		//Debugging Variables
		bool debug{};
		bool verbose{};

	};
}