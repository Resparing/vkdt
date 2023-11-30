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
	VkPipeline* pVKPipeline{};
	VkPipelineLayout* pVKPipelineLayout{};
	VkQueue* pVKGraphicsQueue{};
	VkQueue* pVKPresentQueue{};
	VkRenderPass* pVKRenderPass{};
	VkSurfaceKHR* pVKSurface{};
	VkSwapchainKHR* pVKSwapchain{};

	std::vector<VkImageView>* pSwapImageViews{};
	std::vector<VkImage>* pSwapImages{};
}