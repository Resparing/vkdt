//Include Header File
#include <_vkdt/swapSupportDetail.h>

//Include Headers
#include <_vkdt/pObjects.h>

struct _vkdt::swapSupportDetails::swapchainSupportDetails _vkdt::swapSupportDetails::queueSwapChainSupport
(
	const VkPhysicalDevice& vkdtVKPhysicalDevice
)
{
	//Create Instance of VKDT Vulkan Swapchain Support Details
	_vkdt::swapSupportDetails::swapchainSupportDetails swapSupportDetails = {};

	//Query the Physical Device Surface Details
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkdtVKPhysicalDevice, *_vkdt::pObjects::pVKSurface, &swapSupportDetails.vkdtVKSurfaceDetails);

	//Get Vulkan Surface Formats

	uint32_t vkdtVKSurfaceFormatCount{};

	const VkResult vkdtVKPhysicalDeviceSurfaceFormatCountResult = vkGetPhysicalDeviceSurfaceFormatsKHR
	(
		vkdtVKPhysicalDevice,
		*_vkdt::pObjects::pVKSurface,
		&vkdtVKSurfaceFormatCount,
		nullptr
	);

	if(vkdtVKPhysicalDeviceSurfaceFormatCountResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find Vulkan Surface Format Count! Error: " +
			std::to_string(vkdtVKPhysicalDeviceSurfaceFormatCountResult) +
			"!\n"
		);
	}

	//Resize Vector to add Vulkan Surface Formats
	swapSupportDetails.vkdtVKSurfaceFormats.resize(vkdtVKSurfaceFormatCount);

	const VkResult vkdtVKPhysicalDeviceSurfaceFormatsResult = vkGetPhysicalDeviceSurfaceFormatsKHR
	(
		vkdtVKPhysicalDevice,
		*_vkdt::pObjects::pVKSurface,
		&vkdtVKSurfaceFormatCount,
		swapSupportDetails.vkdtVKSurfaceFormats.data()
	);

	if(vkdtVKPhysicalDeviceSurfaceFormatsResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find Vulkan Surface Formats! Error: " +
			std::to_string(vkdtVKPhysicalDeviceSurfaceFormatsResult) +
			"!\n"
		);
	}

	//Get Vulkan Surface Present Modes

	uint32_t vkdtVKSurfacePresentModeCount{};

	const VkResult vkdtVKPhysicalDeviceSurfacePresentModeCountResult = vkGetPhysicalDeviceSurfacePresentModesKHR
	(
		vkdtVKPhysicalDevice,
		*_vkdt::pObjects::pVKSurface,
		&vkdtVKSurfacePresentModeCount,
		nullptr
	);

	if(vkdtVKPhysicalDeviceSurfacePresentModeCountResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find Vulkan Surface Present Mode Count! Error: " +
			std::to_string(vkdtVKPhysicalDeviceSurfacePresentModeCountResult) +
			"!\n"
		);
	}

	//Resize Vector to add Vulkan Present Modes
	swapSupportDetails.vkdtVKPresentModes.resize(vkdtVKSurfacePresentModeCount);

	const VkResult vkdtVKPhysicalDeviceSurfacePresentModesResult = vkGetPhysicalDeviceSurfacePresentModesKHR
	(
		vkdtVKPhysicalDevice,
		*_vkdt::pObjects::pVKSurface,
		&vkdtVKSurfacePresentModeCount,
		swapSupportDetails.vkdtVKPresentModes.data()
	);

	if(vkdtVKPhysicalDeviceSurfacePresentModesResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find Vulkan Surface Present Modes! Error: " +
			std::to_string(vkdtVKPhysicalDeviceSurfacePresentModesResult) +
			"!\n"
		);
	}

	return swapSupportDetails;
}