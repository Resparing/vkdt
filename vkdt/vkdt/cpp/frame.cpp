//Include Header File
#include <vkdt/frame.h>

//Include Headers
#include <_vkdt/pObjects.h>
#include <vkdt/commandbuffer.h>

vkdt::frame::frame::frame(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vulkan Semaphores & Fences Pointer
	_vkdt::pObjects::pVKImageAvailableSemaphore = &this -> vkdtVKImageAvailableSemaphore;
	_vkdt::pObjects::pVKRenderFinishedSemaphore = &this -> vkdtVKRenderFinishedSemaphore;
	_vkdt::pObjects::pVKInFlightFence = &this -> vkdtVKInFlightFence;

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT Frame!\n";
	}
}

vkdt::frame::frame::~frame()
{
	//Destroy Vulkan Semaphores & Fences
	vkDestroySemaphore(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKImageAvailableSemaphore, this -> pAllocator);
	vkDestroySemaphore(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKRenderFinishedSemaphore, this -> pAllocator);
	vkDestroyFence(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKInFlightFence, this -> pAllocator);

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

	//Vulkan Fence Creation Information Struct
	VkFenceCreateInfo fenceCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,

		//Create the Fence with Signal
		.flags = VK_FENCE_CREATE_SIGNALED_BIT,
	};

	//Vulkan Semaphore Creation Information Struct
	VkSemaphoreCreateInfo semaphoreCreateInfo
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
	};

	//Create Vulkan Image Available Semaphore
	const VkResult createVKImageAvailableSemaphoreResult = vkCreateSemaphore
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		&semaphoreCreateInfo,
		this -> pAllocator,
		&this -> vkdtVKImageAvailableSemaphore
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
			"Failed to Create Vulkan Image Available Semaphore! Error" +
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
		&this -> vkdtVKRenderFinishedSemaphore
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
			"Failed to Create Vulkan Render Finished Semaphore! Error" +
			std::to_string(createVKRenderFinishedSemaphoreResult) +
			"!\n"
		);
	}

	//Create Vulkan In Flight Fence
	const VkResult createVKInFlightFenceResult = vkCreateFence
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		&fenceCreateInfo, this -> pAllocator,
		&this -> vkdtVKInFlightFence
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
		throw std::runtime_error("Failed to Create Vulkan In Flight Fence! Error: " + std::to_string(createVKInFlightFenceResult) + "!\n");
	}

	//Debug Frame Setup Success
	if(this -> debug || this -> verbose)
	{
		std::cout << "Successfully Setup VKDT Frame!\n";
	}
}

void vkdt::frame::frame::drawVKDTFrame(void)
{
	//Wait until Previous Frame Finished
	const VkResult waitForVKFencesResult = vkWaitForFences
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		1,
		&this -> vkdtVKInFlightFence,
		VK_TRUE,
		UINT64_MAX
	);

	if(waitForVKFencesResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Wait for Vulkan Fences! Error: " + std::to_string(waitForVKFencesResult) + "!\n");
	}

	//Manually Reset Fence
	const VkResult resetVKFencesResult = vkResetFences(*_vkdt::pObjects::pVKLogicalDevice, 1, &this -> vkdtVKInFlightFence);

	if(resetVKFencesResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Reset Vulkan Fences! Error: " + std::to_string(resetVKFencesResult) + "!\n");
	}

	//Vulkan Swapchain Image Index
	uint32_t vkdtVKSwapImageIndex{};

	//Find Available Swapchain Index
	const VkResult getNextVKSwapImageResult = vkAcquireNextImageKHR
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		*_vkdt::pObjects::pVKSwapchain,
		UINT64_MAX, this -> vkdtVKImageAvailableSemaphore, VK_NULL_HANDLE, &vkdtVKSwapImageIndex
	);

	if(getNextVKSwapImageResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find Next Swapchain Image Index! Error: " +  std::to_string(getNextVKSwapImageResult) + "!\n");
	}

	//Reset Vulkan Command Buffer
	const VkResult resetVKCommandBufferResult = vkResetCommandBuffer(*_vkdt::pObjects::pVKCommandBuffer, 0);

	if(resetVKCommandBufferResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Reset Vulkan Command Buffer! Error: " + std::to_string(resetVKCommandBufferResult) + "!\n");
	}

	//Record VKDT Command Buffers
	vkdt::commandbuffer::commandbuffer::recordVKCommandBuffer(*_vkdt::pObjects::pVKCommandBuffer, vkdtVKSwapImageIndex);

	//Array of Vulkan Wait Semaphores
	const VkSemaphore vkdtVKWaitSemaphores[] = {this -> vkdtVKImageAvailableSemaphore};

	//Array of Vulkan Signal Semaphores
	const VkSemaphore vkdtVKSignalSemaphores[] = {this -> vkdtVKRenderFinishedSemaphore};

	//Array of Vulkan Pipeline Stage Flags
	const VkPipelineStageFlags vkdtVKWaitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

	//Vulkan Frame Submit Info
	VkSubmitInfo submitInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,

		//Signal Semaphore Information
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = vkdtVKSignalSemaphores,

		//Wait Semaphore Information
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = vkdtVKWaitSemaphores,

		//Vulkan Wait Stages
		.pWaitDstStageMask = vkdtVKWaitStages,

		//Vulkan Command Buffers
		.commandBufferCount = 1,
		.pCommandBuffers = _vkdt::pObjects::pVKCommandBuffer,
	};

	std::cout << *_vkdt::pObjects::pVKImageAvailableSemaphore << " OR " << *_vkdt::pObjects::pVKRenderFinishedSemaphore << "\n";
	std::cout << *_vkdt::pObjects::pVKGraphicsQueue << " OR " << *_vkdt::pObjects::pVKPresentQueue << "\n";

	//Submit Command Buffer to Graphics Queue
	const VkResult submitVKQueueResult = vkQueueSubmit(*_vkdt::pObjects::pVKGraphicsQueue, 1, &submitInfo, this -> vkdtVKInFlightFence);

	if(submitVKQueueResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Submit Command Buffer Info to VKDT Queue! Error: " + std::to_string(submitVKQueueResult) + "!\n");
	}

	//Wait for Command Buffer to Finish Execution
	vkQueueWaitIdle(*_vkdt::pObjects::pVKGraphicsQueue);

	//Array of Vulkan Swapchains
	VkSwapchainKHR vkdtVKSwapChains[] = {*_vkdt::pObjects::pVKSwapchain};

	//Vulkan Present Information Struct
	VkPresentInfoKHR presentInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,

		//Wait Semaphore Information
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = vkdtVKWaitSemaphores,

		//Vulkan Swapchain Information
		.swapchainCount = 1,
		.pSwapchains = vkdtVKSwapChains,

		//Vulkan Image Index
		.pImageIndices = &vkdtVKSwapImageIndex,
	};

	const VkResult presentVKPresentQueueResult = vkQueuePresentKHR(*_vkdt::pObjects::pVKPresentQueue, &presentInfo);

	if(presentVKPresentQueueResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Present VKDT Queue! Error: " + std::to_string(presentVKPresentQueueResult) + "!\n");
	}
}

void vkdt::frame::frame::stopFrame(void)
{
	//Wait for Vulkan Logical Device to Finish Executing
	vkDeviceWaitIdle(*_vkdt::pObjects::pVKLogicalDevice);

	//Debug Idling Success
	if(this -> verbose)
	{
		std::cout << "Successfully Stopped VKDT Frame!\n";
	}
}