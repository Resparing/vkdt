//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace _vkdt::swapSupportDetails
{
	//Struct of Swapchain Support Details
	struct swapchainSupportDetails
	{
		//Vulkan Surface Capabilities
		VkSurfaceCapabilitiesKHR vkdtVKSurfaceDetails;

		//Vector of Vulkan Surface Formats & Present Modes
		std::vector<VkSurfaceFormatKHR> vkdtVKSurfaceFormats;
		std::vector<VkPresentModeKHR> vkdtVKPresentModes;
	};

	/**
	 * @brief Find Vulkan Swapchain Support Details
	 *
	 * @param vkdtVKPhysicalDevice Reference to Vulkan Physical Device
	 *
	 * @return A Struct of Available Surface Support Details
	 */
	struct _vkdt::swapSupportDetails::swapchainSupportDetails queueSwapChainSupport
	(
		const VkPhysicalDevice& vkdtVKPhysicalDevice = VK_NULL_HANDLE
	);
}