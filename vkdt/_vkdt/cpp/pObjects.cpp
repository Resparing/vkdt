//Include Header File
#include <_vkdt/pObjects.h>

namespace _vkdt::pObjects
{
	//Pointers to GLFW Objects
	GLFWwindow** pGLFWWindow{};

	//Pointers to Vulkan Objects
	VkCommandBuffer* pVKCommandBuffer{};
	VkCommandPool* pVKCommandPool{};
	VkDebugUtilsMessengerEXT* pVKDebugMessenger{};
	VkDevice* pVKLogicalDevice{};
	VkExtent2D* pVKSurfaceExtent{};
	VkFormat* pVKSurfaceFormat{};
	VkFence* pVKInFlightFence{};
	VkInstance* pVKInstance{};
	VkPhysicalDevice* pVKPhysicalDevice = VK_NULL_HANDLE;
	VkPipeline* pVKPipeline{};
	VkPipelineLayout* pVKPipelineLayout{};
	VkQueue* pVKGraphicsQueue{};
	VkQueue* pVKPresentQueue{};
	VkRenderPass* pVKRenderPass{};
	VkSemaphore* pVKImageAvailableSemaphore{};
	VkSemaphore* pVKRenderFinishedSemaphore{};
	VkSurfaceKHR* pVKSurface{};
	VkSwapchainKHR* pVKSwapchain{};

	//Pointers to Vectors of Vulkan Objects
	std::vector<VkFramebuffer>* pFrameBuffers{};
	std::vector<VkImageView>* pSwapImageViews{};
	std::vector<VkImage>* pSwapImages{};
}