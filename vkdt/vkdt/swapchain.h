//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace vkdt::swapchain
{
	class swapchain
	{
	public:

		/**
		 * @brief Initialize VKDT Swapchain
		 *
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		swapchain(const bool debug = false, const bool verbose = false) noexcept;

		~swapchain();

		/**
		 * @brief Create VKDT Swapchain
		 *
		 * @param allocator Vulkan Memory Allocator
		 */
		void createVKDTSwapchain(VkAllocationCallbacks* allocator);

	private:

		//Vulkan Memory Allocator
		VkAllocationCallbacks* pAllocator;

		/**
		 * @brief Choose Vulkan Swapchain Surface Format
		 *
		 * @param vkdtVKAvailableFormats A Reference to a Vector of Vulkan Surface Formats
		 *
		 * @return The Selected Vulkan Surface Format
		 */
		VkSurfaceFormatKHR chooseVKSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& vkdtVKAvailableFormats = {}) const noexcept;

		/**
		 * @brief Choose Vulkan Swapchain Surface Present Mode
		 *
		 * @param vkdtVKAvailablePresentModes A Reference to a Vector of Vulkan Surface Present Modes
		 *
		 * @return The Selected Vulkan Surface Present Mode
		 */
		VkPresentModeKHR chooseVKSwapPresentMode(const std::vector<VkPresentModeKHR>& vkdtVKAvailablePresentModes = {}) const noexcept;

		/**
		 * @brief Choose Vulkan Swapchain Extent
		 *
		 * @param vkdtVKAvailablePresentModes A Reference to a Vector of Vulkan Surface Present Modes
		 *
		 * @return The Selected Vulkan Swapchain Extent
		 */
		VkExtent2D chooseVKSwapExtent(const VkSurfaceCapabilitiesKHR& vkdtVKSurfaceCapabilities) const noexcept;

	protected:

		//Vulkan Swapchain
		VkSwapchainKHR vkdtVKSwapchain;

		//Debugging Variables
		bool debug{};
		bool verbose{};

	};
}