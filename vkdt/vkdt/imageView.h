//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace vkdt::imageView
{
	class imageView
	{
	public:

		/**
		 * @brief Initialize VKDT Image View
		 *
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		imageView(const bool debug = false, const bool verbose = false) noexcept;

		~imageView();

		/**
		 * @brief Create VKDT Image Views
		 *
		 * @param allocator Vulkan Memory Allocator
		 */
		void createImageView(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);

	private:

		//Vulkan Memory Allocator
		VkAllocationCallbacks* pAllocator;

		//Vector of Vulkan Swapchain Images
		std::vector<VkImage> vkdtVKSwapchainImages = {};

	protected:

		//Vector of Vulkan Image Views
		std::vector<VkImageView> vkdtVKSwapchainImageViews;

		//Debugging Variables
		bool debug{};
		bool verbose{};

	};
}