//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace _vkdt::pObjects
{
	//Pointers to GLFW Objects
	extern GLFWwindow** pGLFWWindow;  //Pointer to GLFW Window

	//Pointers to Vulkan Objects
	extern VkDebugUtilsMessengerEXT* pVKDebugMessenger;  //Pointer to Vulkan Debug Messenger
	extern VkDevice* pVKLogicalDevice;  //Pointer to Vulkan Logical Device
	extern VkInstance* pVKInstance;  //Pointer to Vulkan Instance
	extern VkPhysicalDevice* pVKPhysicalDevice;  //Pointer to Vulkan Physical Device
	extern VkQueue* pVKGraphicsQueue;  //Pointer to Vulkan Graphics Queue
	extern VkQueue* pVKPresentQueue;  //Pointer to Vulkan Present Queue
	extern VkSurfaceKHR* pVKSurface;  //Pointer to Vulkan Surface
}