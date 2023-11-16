//Include Header File
#include <vkdt/_pObjects.h>

namespace vkdt::_pObjects
{
	//GLFW Objects
	GLFWwindow** pGLFWWindow{};

	//Vulkan Objects
	VkDebugUtilsMessengerEXT* pVKDebugMessenger{};
	VkInstance* pVKInstance{};
	VkDevice* pVKLogicalDevice{};
	VkPhysicalDevice* pVKPhysicalDevice{};
}