//Include Header File
#include <_vkdt/pObjects.h>

namespace _vkdt::pObjects
{
	//Pointers to GLFW Objects
	GLFWwindow** pGLFWWindow{};

	//Pointers to Vulkan Objects
	VkDebugUtilsMessengerEXT* pVKDebugMessenger{};
	VkDevice* pVKLogicalDevice{};
	VkExtent2D* pVKSurfaceExtent{};
	VkFormat* pVKSurfaceFormat{};
	VkInstance* pVKInstance{};
	VkPhysicalDevice* pVKPhysicalDevice = VK_NULL_HANDLE;
	VkQueue* pVKGraphicsQueue{};
	VkQueue* pVKPresentQueue{};
	VkSurfaceKHR* pVKSurface{};
	VkSwapchainKHR* pVKSwapchain{};
}