//Include Header File
#include <vkdt/swapchain.h>

//Include Headers
#include <_vkdt/pObjects.h>
#include <_vkdt/queueFamily.h>
#include <_vkdt/swapSupportDetail.h>

vkdt::swapchain::swapchain::swapchain(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vulkan Swapchain Pointer
	_vkdt::pObjects::pVKSwapchain = &this -> vkdtVKSwapchain;

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT Swapchain!\n";
	}
}

vkdt::swapchain::swapchain::~swapchain()
{
	//Destroy Vulkan Swapchain
	vkDestroySwapchainKHR(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKSwapchain, this -> pAllocator);

	//Debug Deletion Success
	if(this -> verbose)
	{
		std::cout << "Successfully Deleted VKDT Swapchain!\n";
	}
}

void vkdt::swapchain::swapchain::createVKDTSwapchain(VkAllocationCallbacks* allocator)
{
	//Set Vulkan Allocator
	this -> pAllocator = allocator;

	//Get VKDT Swapchain Support Details
	const struct _vkdt::swapSupportDetails::swapchainSupportDetails swapSupportDetails =							\
	_vkdt::swapSupportDetails::queueSwapChainSupport(*_vkdt::pObjects::pVKPhysicalDevice);

	//Get Vulkan Present Mode, Surface Format & Extent
	const VkPresentModeKHR vkdtVKSwapSurfacePresentMode = this -> chooseVKSwapPresentMode(swapSupportDetails.vkdtVKPresentModes);
	VkSurfaceFormatKHR vkdtVKSwapSurfaceFormat = this -> chooseVKSwapSurfaceFormat(swapSupportDetails.vkdtVKSurfaceFormats);
	VkExtent2D vkdtVKSwapSurfaceExtent = this -> chooseVKSwapExtent(swapSupportDetails.vkdtVKSurfaceDetails);

	//Find Number of Images to Have in Vulkan Swapchain
	uint32_t vkdtVKSwapImageBufferNum = swapSupportDetails.vkdtVKSurfaceDetails.minImageCount + 1;

	//Clamp the Value to the Maximum Amount of Allowed Images in Swapchain
	if(swapSupportDetails.vkdtVKSurfaceDetails.maxImageCount > 0)
	{
		if(vkdtVKSwapImageBufferNum > swapSupportDetails.vkdtVKSurfaceDetails.maxImageCount)
		{
			vkdtVKSwapImageBufferNum = swapSupportDetails.vkdtVKSurfaceDetails.maxImageCount;
		}
	}

	//Vulkan Swapchain Creation Information Struct
	VkSwapchainCreateInfoKHR createInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,

		//Vulkan Surface
		.surface = *_vkdt::pObjects::pVKSurface,

		//Minimum Amount of Images in Swapchain
		.minImageCount = vkdtVKSwapImageBufferNum,

		//Surface Format Information
		.imageFormat = vkdtVKSwapSurfaceFormat.format,
		.imageColorSpace = vkdtVKSwapSurfaceFormat.colorSpace,

		//Vulkan Swapchain Image Extent
		.imageExtent = vkdtVKSwapSurfaceExtent,

		//Amount of Layers in Vulkan Image - Only Greater than 1 if Creating Stereoscopic 3D Application
		.imageArrayLayers = 1,

		//What the Images for the Swapchain are used for - Presenting
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

		//How to Share Images Against Queue Families
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,

		//Stop Transformations Happening Inside Swapchain
		.preTransform = swapSupportDetails.vkdtVKSurfaceDetails.currentTransform,

		//Don't Blend with Other Windows
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,

		//Vulkan Present Mode
		.presentMode = vkdtVKSwapSurfacePresentMode,

		//Don't Store Information on Obscured Pixels
		.clipped = VK_TRUE,

		//!TEMPORARY
		.oldSwapchain = VK_NULL_HANDLE,
	};

	//Get Queue Families Indexes
	const struct _vkdt::queueFamily::Indices indexes = _vkdt::queueFamily::findQueueFamilyIndices
	(
		*_vkdt::pObjects::pVKPhysicalDevice,
		false,
		false
	);

	//Array of Vulkan Queue Family Indexes
	const std::array<const uint32_t, 2> vkdtVKQueueFamilyIndexes = {indexes.vkdtVKGraphicsFamily.value(),indexes.vkdtVKPresentFamily.value()};

	//Change Vulkan Swapchain Mode to Concurrent if the Queue Family Indexes are Different
	if(indexes.vkdtVKGraphicsFamily.value() != indexes.vkdtVKPresentFamily.value())
	{
		//Change Image Sharing Mode
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;

		//Add Queue Family Indexes
		createInfo.queueFamilyIndexCount = static_cast<uint32_t>(vkdtVKQueueFamilyIndexes.size());
		createInfo.pQueueFamilyIndices = vkdtVKQueueFamilyIndexes.data();
	}

	//Create Vulkan Swapchain
	const VkResult createVKSwapchainResult = vkCreateSwapchainKHR
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		&createInfo,
		this -> pAllocator,
		&this -> vkdtVKSwapchain
	);

	if(createVKSwapchainResult == VK_SUCCESS)
	{
		if(this -> debug || this -> verbose)
		{
			std::cout << "Successfully Created VKDT Swapchain!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Swapchain! Error: " + std::to_string(createVKSwapchainResult) + "!\n");
	}

	//Set Class Vulkan Surface Format & Extent
	this -> vkdtVKSurfaceFormat = vkdtVKSwapSurfaceFormat.format;
	this -> vkdtVKSurfaceExtent = vkdtVKSwapSurfaceExtent;

	//Set pObject Vulkan Surface Format & Extent
	_vkdt::pObjects::pVKSurfaceFormat = &this -> vkdtVKSurfaceFormat;
	_vkdt::pObjects::pVKSurfaceExtent = &this -> vkdtVKSurfaceExtent;

	//Set Vulkan Swapchain Images Vector
	uint32_t vkdtVKSwapImageCount{};

	const VkResult swapchainImagesCountResult = vkGetSwapchainImagesKHR
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		this -> vkdtVKSwapchain,
		&vkdtVKSwapImageCount,
		nullptr
	);

	if(swapchainImagesCountResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find Number of Vulkan Swapchain Images! Error: " +
			std::to_string(swapchainImagesCountResult) +
			"!\n"
		);
	}

	//Resize Vulkan Swapchain Images Vector
	_vkdt::pObjects::pSwapImages -> resize(vkdtVKSwapImageCount);

	const VkResult swapchainImagesResult = vkGetSwapchainImagesKHR
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		this -> vkdtVKSwapchain,
		&vkdtVKSwapImageCount,
		_vkdt::pObjects::pSwapImages -> data()
	);

	if(swapchainImagesResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find Vulkan Swapchain Images! Error: " + std::to_string(swapchainImagesResult) + "!\n");
	}
}

VkSurfaceFormatKHR vkdt::swapchain::swapchain::chooseVKSwapSurfaceFormat
(
	const std::vector<VkSurfaceFormatKHR>& vkdtVKAvailableFormats
) const noexcept
{
	//Iterate Over Available Vulkan Surface Formats
	for(const VkSurfaceFormatKHR& vkdtVKAvailableFormat : vkdtVKAvailableFormats)
	{
		//Return First Surface Format that Supports Following Items
		if(vkdtVKAvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR && vkdtVKAvailableFormat.format == VK_FORMAT_B8G8R8A8_SRGB)
		{
			if(this -> debug || this -> verbose)
			{
				std::cout << "Successfully Found VKDT Vulkan Swapchain Surface Format!\n";
			}

			return vkdtVKAvailableFormat;
		}
	}

	//If Debugging, Debug Failure to Find Available Surface Format
	if(this -> verbose)
	{
		std::cerr << "Couldn't Find Available VKDT Vulkan Swapchain Surface Format! Defaulting to First Vulkan Swapchain Surface Format...\n";
	}

	//Return the Fist Surface Format if no Surface Formats are Available
	return vkdtVKAvailableFormats[0];
}

VkPresentModeKHR vkdt::swapchain::swapchain::chooseVKSwapPresentMode
(
	const std::vector<VkPresentModeKHR>& vkdtVKAvailablePresentModes
) const noexcept
{
	//Iterate Over Available Surface Present Modes
	for(const VkPresentModeKHR& vkdtVKAvailablePresentMode : vkdtVKAvailablePresentModes)
	{
		//Check if Selected Present Mode Supports Mailbox Present Mode
		if(vkdtVKAvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			if(this -> debug || this -> verbose)
			{
				std::cout << "Successfully Found VKDT Vulkan Swapchain Surface Present Mode: \"VK_PRESENT_MODE_MAILBOX_KHR\"!\n";
			}

			return vkdtVKAvailablePresentMode;
		}
	}

	//If Debugging, Debug Failure to Find Available Surface Present Mode
	if(this -> verbose)
	{
		std::cerr																									\
		<< "Couldn't Find Available VKDT Vulkan Swapchain Surface Present Mode! "									\
		<< "Defaulting to First Vulkan Swapchain Surface Present Mode...\n";
	}

	//Return Guaranteed Vulkan Present Mode if not Found
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D vkdt::swapchain::swapchain::chooseVKSwapExtent(const VkSurfaceCapabilitiesKHR& vkdtVKSurfaceCapabilities) const noexcept
{
	//If the Current Swapchain Extent isn't the Limit of a uin32_t, Return Current Extent
	if(vkdtVKSurfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		//Debug Size
		if(this -> debug || this -> verbose)
		{
			std::cout
			<< "Selected Vulkan Swapchain Extent with Width: " << vkdtVKSurfaceCapabilities.currentExtent.width		\
			<< " Height: " << vkdtVKSurfaceCapabilities.currentExtent.width << "!\n";
		}

		return vkdtVKSurfaceCapabilities.currentExtent;
	}

	//Current Swapchain Extent is Limit of a uint32_t

	//Size of New Extent
	int32_t vkdtVKWidth{};
	int32_t vkdtVKHeight{};

	//Get Window Frame Buffer Size
	glfwGetFramebufferSize(*_vkdt::pObjects::pGLFWWindow, &vkdtVKWidth, &vkdtVKHeight);

	//New Vulkan Extent
	VkExtent2D vkdtVKNewExtent =
	{
		.width = static_cast<uint32_t>(vkdtVKWidth),
		.height = static_cast<uint32_t>(vkdtVKHeight),
	};

	//Camp New Extents to Minimum and Maximum Vulkan Surface Image Extent
	vkdtVKNewExtent.width = std::clamp
	(
		vkdtVKNewExtent.width,
		vkdtVKSurfaceCapabilities.minImageExtent.width,
		vkdtVKSurfaceCapabilities.maxImageExtent.width
	);

	vkdtVKNewExtent.height = std::clamp
	(
		vkdtVKNewExtent.height,
		vkdtVKSurfaceCapabilities.minImageExtent.height,
		vkdtVKSurfaceCapabilities.maxImageExtent.height
	);

	if(this -> debug || this -> verbose)
	{
		std::cout
		<< "Selected Vulkan Swapchain Extent with Width: " << vkdtVKNewExtent.width		\
		<< " Height: " << vkdtVKNewExtent.width << "!\n";
	}

	return vkdtVKNewExtent;
}