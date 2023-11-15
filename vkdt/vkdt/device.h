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
		 * @param vkdtGPU Pointer to VKDT GPU
		 * @param vkdtVKRequestedExtensions C-String Vector of Requested VKDT Vulkan Extensions
		 * @param vkdtVKRequestedLayers C-String Vector of Requested VKDT Vulkan Extensions
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		device
		(
			vkdt::GPU::GPU* vkdtGPU,
			const std::vector<const char*> vkdtVKRequestedExtensions = {},
			const std::vector<const char*> vkdtVKRequestedLayers = {},
			const bool debug = false,
			const bool verbose = false
		) noexcept;

		virtual ~device();

		/**
		 * @brief Create VKDT Device
		 *
		 * @param vkdtGraphicsQueue Vulkan Graphics Queue
		 * @param allocator Vulkan Memory Allocator
		 */
		void createVKDTDevice(vkdt::queue::queue* vkdtGraphicsQueue, VkAllocationCallbacks* allocator = VK_NULL_HANDLE);

		/**
		 * @brief Get a Reference to VKDT Vulkan Logical Device
		 *
		 * @attention Use for Extending VKDT Device Class and for Internal Use!
		 *
		 * @return Reference to Vulkan Physical Device
		 */
		const VkDevice& refVKLogicalDevice() const noexcept;

	private:

		//Vulkan Layers & Extensions
		std::vector<const char*> vkdtVKLayers;
		std::vector<const char*> vkdtVKExtensions;

		//Vulkan Allocator
		VkAllocationCallbacks* pAllocator;

	protected:

		/* Vulkan Parameters */
		VkPhysicalDevice* pVKPhysicalDevice;  //Pointer to Vulkan Physical Device
		VkDevice vkdtVKLogicalDevice;  //Vulkan Logical Device

		//Debugging Variables
		bool debug{};
		bool verbose{};
	};
}