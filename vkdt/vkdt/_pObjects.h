//Header Guard
#pragma once

//Include Headers
#include <vkdt/_vkdtConfig.h>

namespace vkdt::_pObjects
{
	/* Pointers to GLFW Objects */
	extern GLFWwindow** pGLFWWindow;  //Pointer to GLFW Window

	/* Pointers to Vulkan Objects */
	extern VkDebugUtilsMessengerEXT* pVKDebugMessenger;  //Pointer to Vulkan Debug Messenger
	extern VkInstance* pVKInstance;  //Pointer to Vulkan Instance
	extern VkDevice* pVKLogicalDevice;  //Pointer to Vulkan Logical Device
	extern VkPhysicalDevice* pVKPhysicalDevice;  //Pointer to Vulkan Physical Device
}