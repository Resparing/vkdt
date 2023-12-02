//Include Header File
#include <vkdt/imageView.h>

//Include Headers
#include <_vkdt/pObjects.h>

vkdt::imageView::imageView::imageView(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vector of Vulkan Swapchain Images & Image Views Pointers
	_vkdt::pObjects::pSwapImages = &this -> vkdtVKSwapchainImages;
	_vkdt::pObjects::pSwapImageViews = &this -> vkdtVKSwapchainImageViews;

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT Image Views!\n";
	}
}

vkdt::imageView::imageView::~imageView()
{
	//Iterate over Swapchain Image Views
	for(const VkImageView& vkdtVKSwapchainImageView : this -> vkdtVKSwapchainImageViews)
	{
		vkDestroyImageView(*_vkdt::pObjects::pVKLogicalDevice, vkdtVKSwapchainImageView, this -> pAllocator);
	}

	//Debug Deletion Success
	if(this -> verbose)
	{
		std::cout << "Successfully Destroyed VKDT Image View!\n";
	}
}

void vkdt::imageView::imageView::createVKDTImageView(VkAllocationCallbacks* allocator)
{
	//Set Vulkan Allocator
	this -> pAllocator = allocator;

	//Resize Swapchain Image Views Vector to Swapchain Images Vector
	this -> vkdtVKSwapchainImageViews.resize(this -> vkdtVKSwapchainImages.size());

	//Debug Number of Vulkan Swapchain Image View
	if(this -> debug || this -> verbose)
	{
		std::cout << "Creating: " << vkdtVKSwapchainImageViews.size() << "...\n";
	}

	//Iterate Over Vulkan Swapchain Images
	for(size_t i{}; i < this -> vkdtVKSwapchainImages.size(); ++i)
	{
		//Vulkan Image View Creation Information Struct
		VkImageViewCreateInfo createInfo =
		{
			//Struct Type
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,

			//Corresponding Vulkan Swapchain Image
			.image = this -> vkdtVKSwapchainImages[i],

			//Vulkan Image Views Type
			.viewType = VK_IMAGE_VIEW_TYPE_2D,

			//Selected Surface Format
			.format = *_vkdt::pObjects::pVKSurfaceFormat,

			//Default Color Mapping
			.components =
			{
				.r = VK_COMPONENT_SWIZZLE_IDENTITY,
				.g = VK_COMPONENT_SWIZZLE_IDENTITY,
				.b = VK_COMPONENT_SWIZZLE_IDENTITY,
				.a = VK_COMPONENT_SWIZZLE_IDENTITY,
			},

			//Image Purpose
			.subresourceRange =
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseArrayLayer = 0,
				.baseMipLevel = 0,
				.levelCount = 1,
				.layerCount = 1,
			},
		};

		//Create Vulkan Image View
		const VkResult createImageViewResult = vkCreateImageView
		(
			*_vkdt::pObjects::pVKLogicalDevice,
			&createInfo,
			this -> pAllocator,
			&this -> vkdtVKSwapchainImageViews[i]
		);

		if(createImageViewResult == VK_SUCCESS)
		{
			if(this -> verbose)
			{
				std::cout << "\tSuccessfully Created VKDT Image View No: " << i << "!\n";
			}
		}
		else
		{
			throw std::runtime_error
			(
				"Failed to Create VKDT Image View No: " + std::to_string(i) +
				"! Error: " + std::to_string(createImageViewResult) +
				"!\n"
			);
		}
	}

	//Debug Initialization Success
	if(this -> debug || this -> verbose)
	{
		std::cout << "Successfully Finished Creating VKDT Image View!\n";
	}
}