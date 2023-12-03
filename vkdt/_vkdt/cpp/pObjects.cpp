//Include Header File
#include <_vkdt/pObjects.h>

namespace _vkdt::pObjects
{
	//Pointers to GLFW Objects
	GLFWwindow** pGLFWWindow{};

	//Pointers to Vulkan Objects
	VkCommandPool* pVKCommandPool{};
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

	//Pointers to Vectors of Vulkan Objects
	std::vector<VkCommandBuffer>* pCommandBuffers{};
	std::vector<VkFence>* pInFlightFences{};
	std::vector<VkFramebuffer>* pFrameBuffers{};
	std::vector<VkImageView>* pSwapImageViews{};
	std::vector<VkImage>* pSwapImages{};
	std::vector<VkSemaphore>* pImageAvailableSemaphores{};
	std::vector<VkSemaphore>* pRenderFinishedSemaphores{};
}