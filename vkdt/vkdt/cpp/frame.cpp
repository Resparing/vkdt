//Include Header File
#include <vkdt/frame.h>

//Include Headers
#include <_vkdt/pObjects.h>
#include <vkdt/commandbuffer.h>

vkdt::frame::frame::frame(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vulkan Semaphores & Fences Pointer
	_vkdt::pObjects::pImageAvailableSemaphores = &this -> vkdtVKImageAvailableSemaphores;
	_vkdt::pObjects::pRenderFinishedSemaphores = &this -> vkdtVKRenderFinishedSemaphores;
	_vkdt::pObjects::pInFlightFences = &this -> vkdtVKInFlightFences;

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT Frame!\n";
	}
}

vkdt::frame::frame::~frame()
{
	//Repeat for Max Frames in Flight
	for(size_t i{}; i < _vkdt::pObjects::pCommandBuffers -> size(); ++i)
	{
		//Destroy Vulkan Semaphores & In-Flight Fence
		vkDestroySemaphore(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKImageAvailableSemaphores[i], this -> pAllocator);
		vkDestroySemaphore(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKRenderFinishedSemaphores[i], this -> pAllocator);
		vkDestroyFence(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKInFlightFences[i], this -> pAllocator);
	}

	//Debug Destruction Success
	if(this -> verbose)
	{
		std::cout << "Successfully Destroyed VKDT Frame!\n";
	}
}

void vkdt::frame::frame::setupVKDTFrame(VkAllocationCallbacks* allocator)
{
	//Set Vulkan Memory Allocator
	this -> pAllocator = allocator;

	//Resize Semaphore & Fences Vectors to Command Buffer Size
	this -> vkdtVKImageAvailableSemaphores.resize(_vkdt::pObjects::pCommandBuffers -> size());
	this -> vkdtVKRenderFinishedSemaphores.resize(_vkdt::pObjects::pCommandBuffers -> size());
	this -> vkdtVKInFlightFences.resize(_vkdt::pObjects::pCommandBuffers -> size());

	//Vulkan Semaphore Creation Information Struct
	VkSemaphoreCreateInfo semaphoreCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
	};

	//Vulkan Fence Creation Information Struct
	VkFenceCreateInfo fenceCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,

		//Create Fence With Signal
		.flags = VK_FENCE_CREATE_SIGNALED_BIT,
	};

	//Repeat for Max Frames in Flight
	for(size_t i{}; i < _vkdt::pObjects::pCommandBuffers -> size(); ++i)
	{
		//Create Vulkan Image Available Semaphore
		const VkResult createVKImageAvailableSemaphoreResult = vkCreateSemaphore
		(
			*_vkdt::pObjects::pVKLogicalDevice,
			&semaphoreCreateInfo,
			this -> pAllocator,
			&this -> vkdtVKImageAvailableSemaphores[i]
		);

		if(createVKImageAvailableSemaphoreResult == VK_SUCCESS)
		{
			//Debug Creation Success
			if(this -> verbose)
			{
				std::cout << "Successfully Created Vulkan Image Available Semaphore!\n";
			}
		}
		else
		{
			throw std::runtime_error
			(
				"Failed to Create Vulkan Image Available Semaphore! Error: " +
				std::to_string(createVKImageAvailableSemaphoreResult) +
				"!\n"
			);
		}

		//Create Vulkan Render Finished Semaphore
		const VkResult createVKRenderFinishedSemaphoreResult = vkCreateSemaphore
		(
			*_vkdt::pObjects::pVKLogicalDevice,
			&semaphoreCreateInfo,
			this -> pAllocator,
			&this -> vkdtVKRenderFinishedSemaphores[i]
		);

		if(createVKRenderFinishedSemaphoreResult == VK_SUCCESS)
		{
			//Debug Creation Success
			if(this -> verbose)
			{
				std::cout << "Successfully Created Vulkan Render Finished Semaphore!\n";
			}
		}
		else
		{
			throw std::runtime_error
			(
				"Failed to Create Vulkan Render Finished Semaphore! Error: " +
				std::to_string(createVKRenderFinishedSemaphoreResult) +
				"!\n"
			);
		}

		//Create Vulkan In-Flight Fence
		const VkResult createVKInFlightFenceResult = vkCreateFence
		(
			*_vkdt::pObjects::pVKLogicalDevice,
			&fenceCreateInfo,
			this -> pAllocator,
			&this -> vkdtVKInFlightFences[i]
		);

		if(createVKInFlightFenceResult == VK_SUCCESS)
		{
			//Debug Creation Success
			if(this -> verbose)
			{
				std::cout << "Successfully Created Vulkan In Flight Fence!\n";
			}
		}
		else
		{
			throw std::runtime_error
			(
				"Failed to Create Vulkan In-Flight Fence! Error: " +
				std::to_string(createVKInFlightFenceResult) +
				"!\n"
			);
		}
	}

	//Debug Frame Initialization Success
	if(this -> debug || this -> verbose)
	{
		std::cout << "Successfully Setup VKDT Frame!\n";
	}
}

void vkdt::frame::frame::drawVKDTFrame(void)
{
	//Index of Current Frame
	uint32_t vkdtCurrentFrame{};

	//Wait for Last Frame to Finish Rendering
	const VkResult waitForVKFencesResult = vkWaitForFences
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		1,
		&this -> vkdtVKInFlightFences[vkdtCurrentFrame],
		VK_TRUE,
		UINT64_MAX
	);

	if(waitForVKFencesResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Wait for Previous Frame! Error: " + std::to_string(waitForVKFencesResult) + "!\n");
	}

	//Reset Vulkan Command Buffer
	const VkResult resetVKFencesResult = vkResetFences(*_vkdt::pObjects::pVKLogicalDevice, 1, &this -> vkdtVKInFlightFences[vkdtCurrentFrame]);

	if(resetVKFencesResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Reset VKDT Command Buffer! Error: " + std::to_string(resetVKFencesResult) + "!\n");
	}

	//Vulkan Swapchain Image Index
	uint32_t vkdtVKSwapImageIndex{};

	//Get VKDT Swapchain Image Index
	const VkResult getVKSwapImageIndexResult = vkAcquireNextImageKHR
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		*_vkdt::pObjects::pVKSwapchain,
		UINT64_MAX,
		this -> vkdtVKImageAvailableSemaphores[vkdtCurrentFrame],
		VK_NULL_HANDLE,
		&vkdtVKSwapImageIndex
	);

	if(getVKSwapImageIndexResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find VKDT Swapchain Index! Error:" + std::to_string(getVKSwapImageIndexResult) + "!\n");
	}

	//Reset Vulkan Command Buffer
	const VkResult resetVkCommandBufferResult = vkResetCommandBuffer((*_vkdt::pObjects::pCommandBuffers)[vkdtCurrentFrame], 0);

	if(resetVkCommandBufferResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Reset Vulkan Command Buffer! Error: " + std::to_string(resetVkCommandBufferResult) + "!\n");
	}

	//Record Vulkan Command Buffer
	vkdt::commandbuffer::commandbuffer::recordVKCommandBuffer((*_vkdt::pObjects::pCommandBuffers)[vkdtCurrentFrame], vkdtVKSwapImageIndex);

	//Vulkan Wait & Signal Semaphores
	VkSemaphore vkdtVKWaitSemaphores[] = {this -> vkdtVKImageAvailableSemaphores[vkdtCurrentFrame]};
	VkSemaphore vkdtVKSignalSemaphores[] = {this -> vkdtVKRenderFinishedSemaphores[vkdtCurrentFrame]};

	//Vulkan Pipeline Stages
	VkPipelineStageFlags vkdtVkWaitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

	//Vulkan Submit Information Struct
	VkSubmitInfo submitInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,

		//Vulkan Wait Semaphores Information
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = vkdtVKWaitSemaphores,

		//Vulkan Signal Semaphores Information
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = vkdtVKSignalSemaphores,

		//Vulkan Wait Stages
		.pWaitDstStageMask = vkdtVkWaitStages,

		//Vulkan Command Buffer Information
		.commandBufferCount = 1,
		.pCommandBuffers = &(*_vkdt::pObjects::pCommandBuffers)[vkdtCurrentFrame],
	};

	//Submit VKDT Queue
	const VkResult submitVkQueueResult = vkQueueSubmit
	(
		*_vkdt::pObjects::pVKGraphicsQueue,
		1, &submitInfo,
		this -> vkdtVKInFlightFences[vkdtCurrentFrame]
	);

	if(submitVkQueueResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Submit Vulkan Graphics Queue! Error: " + std::to_string(submitVkQueueResult) + "!\n");
	}

	//Array of Vulkan Swapchains
	const VkSwapchainKHR vkdtVKSwapchains[] = {*_vkdt::pObjects::pVKSwapchain};

	VkPresentInfoKHR vkdtVKPresentInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,

		//Vulkan Wait Semaphores Information
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = vkdtVKSignalSemaphores,

		//Vulkan Swapchain Information
		.swapchainCount = 1,
		.pSwapchains = vkdtVKSwapchains,

		//Swapchain Image Index
		.pImageIndices = &vkdtVKSwapImageIndex
	};

	//Show Frame to Screen
	const VkResult presentVKQueueResult = vkQueuePresentKHR(*_vkdt::pObjects::pVKPresentQueue, &vkdtVKPresentInfo);

	if(presentVKQueueResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Draw VKDT Frame! Error:" + std::to_string(presentVKQueueResult) + "!\n");
	}

	//Advance Current Frame
	vkdtCurrentFrame = (vkdtCurrentFrame + 1) % _vkdt::pObjects::pCommandBuffers -> size();
}

void vkdt::frame::frame::stopVKDTFrame(void)
{
	//Wait for Vulkan Logical Device to Finish Executing
	const VkResult waitForVKLogicalDeviceResult = vkDeviceWaitIdle(*_vkdt::pObjects::pVKLogicalDevice);

	if(waitForVKLogicalDeviceResult == VK_SUCCESS)
	{
		//Debug Idling Success
		if(this -> verbose)
		{
			std::cout << "Successfully Stopped VKDT Frame!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Wait for VKDT Device to Stop! Error: " + std::to_string(waitForVKLogicalDeviceResult) + "!\n");
	}
}