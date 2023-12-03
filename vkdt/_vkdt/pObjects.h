//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace _vkdt::pObjects
{
	//Pointers to GLFW Objects
	extern GLFWwindow** pGLFWWindow;  //Pointer to GLFW Window

	//Pointers to Vulkan Objects
	extern VkCommandPool* pVKCommandPool;  //Pointer to Vulkan Command Pool
	extern VkDebugUtilsMessengerEXT* pVKDebugMessenger;  //Pointer to Vulkan Debug Messenger
	extern VkDevice* pVKLogicalDevice;  //Pointer to Vulkan Logical Device
	extern VkExtent2D* pVKSurfaceExtent;  //Pointer to Vulkan Surface Extent
	extern VkFormat* pVKSurfaceFormat;  //Pointer to Vulkan Surface Format
	extern VkInstance* pVKInstance;  //Pointer to Vulkan Instance
	extern VkPhysicalDevice* pVKPhysicalDevice;  //Pointer to Vulkan Physical Device
	extern VkPipeline* pVKPipeline;  //Pointer to Vulkan Pipeline
	extern VkPipelineLayout* pVKPipelineLayout;  //Pointer to Vulkan Pipeline Layout
	extern VkQueue* pVKGraphicsQueue;  //Pointer to Vulkan Graphics Queue
	extern VkQueue* pVKPresentQueue;  //Pointer to Vulkan Present Queue
	extern VkRenderPass* pVKRenderPass;  //Pointer to Vulkan Render Pass
	extern VkSurfaceKHR* pVKSurface;  //Pointer to Vulkan Surface
	extern VkSwapchainKHR* pVKSwapchain;  //Pointer to Vulkan Swapchain

	//Pointers to Vectors of Vulkan Objects
	extern std::vector<VkCommandBuffer>* pCommandBuffers;  //Pointer to Vector of Vulkan Command Buffers
	extern std::vector<VkFence>* pInFlightFences;  //Pointer to Vector of Vulkan Vulkan In Flight Fences
	extern std::vector<VkFramebuffer>* pFrameBuffers;  //Pointer to Vector of Vulkan Framebuffers
	extern std::vector<VkImageView>* pSwapImageViews;  //Pointer to Vector of Vulkan Swapchain Image Views
	extern std::vector<VkImage>* pSwapImages;  //Pointer to Vector of Vulkan Swapchain Images
	extern std::vector<VkSemaphore>* pImageAvailableSemaphores;  //Pointer to Vector ofVulkan Image Available Semaphores
	extern std::vector<VkSemaphore>* pRenderFinishedSemaphores;  //Pointer to Vector ofVulkan Render Finished Semaphores
}