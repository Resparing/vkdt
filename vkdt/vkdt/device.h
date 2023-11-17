//Header Guard
#pragma once

//Include Headers
#include <vkdt/_vkdtConfig.h>
#include <vkdt/GPU.h>
#include <vkdt/queue.h>

namespace vkdt::device
{
	class device
	{
	public:

		/**
		 * @brief Initialize VKDT Device
		 *
		 * @param vkdtVKRequestedExtensions C-String Vector of Requested VKDT Vulkan Extensions
		 * @param vkdtVKRequestedLayers C-String Vector of Requested VKDT Vulkan Extensions
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		device
		(
			const std::vector<const char*>& vkdtVKRequestedExtensions = {},
			const std::vector<const char*>& vkdtVKRequestedLayers = {},
			const bool debug = false,
			const bool verbose = false
		) noexcept;

		virtual ~device();

		/**
		 * @brief Create VKDT Device
		 *
		 * @param allocator Vulkan Memory Allocator
		 */
		void createVKDTDevice(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);

	private:

		//Vulkan Layers & Extensions
		std::vector<const char*> vkdtVKLayers;
		std::vector<const char*> vkdtVKExtensions;

		//Vulkan Allocator
		VkAllocationCallbacks* pAllocator;

	protected:

		/* Vulkan Parameters */
		VkDevice vkdtVKLogicalDevice;  //Vulkan Logical Device

		//Debugging Variables
		bool debug{};
		bool verbose{};
	};
}