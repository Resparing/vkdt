//Include Header File
#include <vkdt/_pObjects.h>

namespace vkdt::_pObjects
{
	//Pointers to GLFW Objects
	GLFWwindow** pGLFWWindow{};

	//Pointers to Vulkan Objects
	VkDebugUtilsMessengerEXT* pVKDebugMessenger{};
	VkDevice* pVKLogicalDevice{};
	VkInstance* pVKInstance{};
	VkPhysicalDevice* pVKPhysicalDevice{};
	VkQueue* pVKGraphicsQueue{};
	VkQueue* pVKPresentQueue{};
	VkSurfaceKHR* pVKSurface{};
}