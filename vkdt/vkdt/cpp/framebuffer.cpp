//Include Header File
#include <vkdt/framebuffer.h>

//Include Headers
#include <_vkdt/pObjects.h>

vkdt::framebuffer::framebuffer::framebuffer(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vector to Vulkan Frame Buffers & Class Pointers
	_vkdt::pObjects::pFrameBuffers = &this -> vkdtVKFrameBuffers;
	_vkdt::pObjects::pVKDTFrameBuffer = this;

	//Set Frame Buffer Size to Swapchain Image Views Vector Size
	this -> vkdtVKFrameBuffers.resize(_vkdt::pObjects::pSwapImageViews -> size());

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT Frame Buffer!\n";
	}
}

vkdt::framebuffer::framebuffer::~framebuffer()
{
	//Iterate Over Vulkan Frame Buffers
	for(const VkFramebuffer& vkdtVKFrameBuffer : vkdtVKFrameBuffers)
	{
		vkDestroyFramebuffer(*_vkdt::pObjects::pVKLogicalDevice, vkdtVKFrameBuffer, this -> pAllocator);
	}

	//Debug Destruction Success
	if(this -> verbose)
	{
		std::cout << "Successfully Destroyed VKDT Frame Buffer!\n";
	}
}

void vkdt::framebuffer::framebuffer::createVKDTFramebuffer(VkAllocationCallbacks* allocator)
{
	//Set Vulkan Memory Allocator
	this -> pAllocator = allocator;

	//Iterate Over Empty Frame Buffer Vector
	for(size_t i{}; i < _vkdt::pObjects::pSwapImageViews -> size(); ++i)
	{
		//Array of Vulkan Image View Attachments, Get Corresponding Vulkan Swapchain Image View
		std::array<VkImageView, 1> imageViews = {(*_vkdt::pObjects::pSwapImageViews)[i]};

		//Vulkan Frame Buffer Creation Information Struct
		VkFramebufferCreateInfo createInfo =
		{
			//Struct Type
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,

			//Vulkan Renderpass
			.renderPass = *_vkdt::pObjects::pVKRenderPass,

			//Vulkan Attachments
			.attachmentCount = static_cast<uint32_t>(imageViews.size()),
			.pAttachments = imageViews.data(),

			//Swapchain Extent Size
			.width = _vkdt::pObjects::pVKSurfaceExtent -> width,
			.height = _vkdt::pObjects::pVKSurfaceExtent -> height,

			//Number of Layers in Image Arrays
			.layers = 1,
		};

		//Create Vulkan Framebuffer
		const VkResult createVKFramebufferResult = vkCreateFramebuffer
		(
			*_vkdt::pObjects::pVKLogicalDevice,
			&createInfo,
			this -> pAllocator,
			&this -> vkdtVKFrameBuffers[i]
		);

		if(createVKFramebufferResult == VK_SUCCESS)
		{
			//Debug Creation Success
			if(this -> verbose)
			{
				std::cout << "\tSuccessfully Create VKDT Framebuffer No: " << i + 1 << "!\n";
			}
		}
		else
		{
			throw std::runtime_error
			(
				"Failed to Create VKDT Framebuffer No: " + std::to_string(i + 1) +
				"! Error: " + std::to_string(createVKFramebufferResult)
				+ "!\n"
			);
		}
	}

	//Debug Creation Success
	if(this -> debug || this -> verbose)
	{
		std::cout << "Successfully Created: " << _vkdt::pObjects::pSwapImageViews -> size() << " VKDT Framebuffer!\n";
	}
}