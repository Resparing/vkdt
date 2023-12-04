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

	//Pointers to VKDT Objects
	vkdt::commandbuffer::commandbuffer* pVKDTCommandBuffer{};
	vkdt::debug::messenger* pVKDTDebugMessenger{};
	vkdt::device::device* pVKDTDevice{};
	vkdt::frame::frame* pVKDTFrame{};
	vkdt::framebuffer::framebuffer* pVKDTFrameBuffer{};
	vkdt::GPU::GPU* pVKDTGPU{};
	vkdt::imageview::imageview* pVKDTImageView{};
	vkdt::instance::instance* pVKDTInstance{};
	vkdt::pipeline::pipeline* pVKDTPipeline{};
	vkdt::queue::queue* pVKDTQueue{};
	vkdt::surface::surface* pVKDTSurface{};
	vkdt::swapchain::swapchain* pVKDTSwapchain{};
	vkdt::window::window* pVKDTWindow{};
}