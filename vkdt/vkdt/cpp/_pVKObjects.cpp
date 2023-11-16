//Include Header File
#include <vkdt/_pVKObjects.h>

namespace vkdt::_pVKObjects
{
	//GLFW Objects
	GLFWwindow** pGLFWWindow{};

	//Vulkan Objects
	VkDebugUtilsMessengerEXT* pVKDebugMessenger{};
	VkInstance* pVKInstance{};
	VkDevice* pVKLogicalDevice{};
	VkPhysicalDevice* pVKPhysicalDevice{};
}