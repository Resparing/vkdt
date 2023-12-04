//Include Header File
#include <vkdt/commandbuffer.h>

//Include Headers
#include <_vkdt/pObjects.h>
#include <_vkdt/queueFamily.h>

vkdt::commandbuffer::commandbuffer::commandbuffer(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vulkan Command Pool Pointer
	_vkdt::pObjects::pVKCommandPool = &this -> vkdtVKCommandPool;
	_vkdt::pObjects::pCommandBuffers = &this -> vkdtVKCommandBuffers;

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT Command Buffer!\n";
	}
}

vkdt::commandbuffer::commandbuffer::~commandbuffer()
{
	//Destroy Vulkan Command Pool
	vkDestroyCommandPool(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKCommandPool, this -> pAllocator);

	//Debug Destruction Success
	if(this -> verbose)
	{
		std::cout << "Successfully Destroyed VKDT Command Buffer!\n";
	}
}

void vkdt::commandbuffer::commandbuffer::createVKDTCommandbuffer(VkAllocationCallbacks* allocator)
{
	//Set Vulkan Memory Allocator
	this -> pAllocator = allocator;

	//Get VKDT Queue Family Indexes
	struct _vkdt::queueFamily::Indices indexes = _vkdt::queueFamily::findQueueFamilyIndices(*_vkdt::pObjects::pVKPhysicalDevice, false, false);

	//Vulkan Command Pool Creation Information Struct
	VkCommandPoolCreateInfo createInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,

		//Allow Individual Command Pool Resetting
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,

		//Queue Family Index
		.queueFamilyIndex = indexes.vkdtVKGraphicsFamily.value(),
	};

	//Create Vulkan Command Pool
	const VkResult createVKCommandPoolResult = vkCreateCommandPool
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		&createInfo,
		this -> pAllocator,
		&this -> vkdtVKCommandPool
	);

	if(createVKCommandPoolResult == VK_SUCCESS)
	{
		//Debug Creation Success
		if(this -> verbose)
		{
			std::cout << "Successfully Created VKDT Command Pool!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Command Buffer! Error: " + std::to_string(createVKCommandPoolResult) + "!\n");
	}

	//Resize Vector of Vulkan Command Buffers
	this -> vkdtVKCommandBuffers.resize(static_cast<size_t>(this -> MAX_FRAMES));

	//Vulkan Command Buffer Allocation Information Struct
	VkCommandBufferAllocateInfo allocInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,

		//Command Pool
		.commandPool = this -> vkdtVKCommandPool,

		//Command Buffer Level
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,

		//Allocate Two Command Buffers
		.commandBufferCount = static_cast<uint32_t>(this -> vkdtVKCommandBuffers.size()),
	};

	//Allocate Vulkan Command Buffer
	const VkResult allocVKCommandBufferResult = vkAllocateCommandBuffers
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		&allocInfo,
		this -> vkdtVKCommandBuffers.data()
	);

	if(allocVKCommandBufferResult == VK_SUCCESS)
	{
		//Debug Creation Success
		if(this -> debug || this -> verbose)
		{
			std::cout << "Successfully Created VKDT Command Buffer!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Command Buffer! Error: " + std::to_string(allocVKCommandBufferResult) + "!\n");
	}
}

void vkdt::commandbuffer::commandbuffer::recordVKCommandBuffer(const VkCommandBuffer& commandBuffer, const uint32_t index)
{
	//Vulkan Command Buffer Beginning Information Struct
	VkCommandBufferBeginInfo commandBufferBeginInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
	};

	//Begin Vulkan Command Buffer
	const VkResult recordVKCommandBufferResult = vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo);

	if(recordVKCommandBufferResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Being Command Buffer! Error: " + std::to_string(recordVKCommandBufferResult) + "!\n");
	}

	//Background Color
	VkClearValue vkdtVKClearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};

	//Vulkan Render Pass Beginning Information Struct
	VkRenderPassBeginInfo renderpassBeginInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,

		//Render Pass
		.renderPass = *_vkdt::pObjects::pVKRenderPass,

		//Current Frame Buffer
		.framebuffer = (*_vkdt::pObjects::pFrameBuffers)[index],

		//Render Area
		.renderArea =
		{
			//Offset
			.offset = {0, 0},

			//Swapchain Extent
			.extent = *_vkdt::pObjects::pVKSurfaceExtent,
		},

		//Clear Values
		.clearValueCount = 1,
		.pClearValues = &vkdtVKClearColor,
	};

	//Begin the Renderpass & Bind Pipeline
	vkCmdBeginRenderPass(commandBuffer, &renderpassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *_vkdt::pObjects::pVKPipeline);

	//Vulkan Viewport Information Struct
	VkViewport viewport =
	{
		//Position
		.x = 0.0f,
		.y = 0.0f,

		//Size
		.width = static_cast<float>(_vkdt::pObjects::pVKSurfaceExtent -> width),
		.height = static_cast<float>(_vkdt::pObjects::pVKSurfaceExtent -> height),

		//Depth
		.minDepth = 0.0f,
		.maxDepth = 1.0f,
	};

	//Vulkan Scissor
	VkRect2D scissor =
	{
		//Offset
		.offset = {0, 0},

		//Surface Extent
		.extent = *_vkdt::pObjects::pVKSurfaceExtent,
	};

	//Set Vulkan Viewport & Scissor
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	//!TEMPORARY - Draw Triangle
	vkCmdDraw(commandBuffer, 3, 1, 0, 0);

	//End Render Pass
	vkCmdEndRenderPass(commandBuffer);

	//Finish Recording Command Buffer
	const VkResult endRecordCommandBufferResult = vkEndCommandBuffer(commandBuffer);

	if(endRecordCommandBufferResult != VK_SUCCESS)
	{
    	throw std::runtime_error("failed to End Recording Command Buffer! Error: " + std::to_string(endRecordCommandBufferResult) + "!\n");
	}
}