//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>
#include <vkdt/commandbuffer.h>
#include <vkdt/debug.h>
#include <vkdt/device.h>
#include <vkdt/frame.h>
#include <vkdt/framebuffer.h>
#include <vkdt/GPU.h>
#include <vkdt/imageview.h>
#include <vkdt/instance.h>
#include <vkdt/pipeline.h>
#include <vkdt/queue.h>
#include <vkdt/surface.h>
#include <vkdt/swapchain.h>
#include <vkdt/window.h>

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

	//Pointers to VKDT Objects
	extern vkdt::commandbuffer::commandbuffer* pVKDTCommandBuffer;  //Pointer to VKDT Command Buffer
	extern vkdt::debug::messenger* pVKDTDebugMessenger;  //Pointer to VKDT Debug Messenger
	extern vkdt::device::device* pVKDTDevice;  //Pointer to VKDT Device
	extern vkdt::frame::frame* pVKDTFrame;  //Pointer to VKDT Frame
	extern vkdt::framebuffer::framebuffer* pVKDTFrameBuffer;  //Pointer to VKDT Frame Buffer
	extern vkdt::GPU::GPU* pVKDTGPU;  //Pointer to VKDT GPU
	extern vkdt::imageview::imageview* pVKDTImageView;  //Pointer to VKDT Iamge View
	extern vkdt::instance::instance* pVKDTInstance;  //Pointer to VKDT Instance
	extern vkdt::pipeline::pipeline* pVKDTPipeline;  //Pointer to VKDT Pipeline
	extern vkdt::queue::queue* pVKDTQueue;  //Pointer to VKDT Queues
	extern vkdt::surface::surface* pVKDTSurface;  //Pointer to VKDT Surface
	extern vkdt::swapchain::swapchain* pVKDTSwapchain;  //Pointer to VKDT Swapchain
	extern vkdt::window::window* pVKDTWindow;  //Pointer to VKDT Window
}