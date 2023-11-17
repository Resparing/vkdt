//Include Header File
#include <vkdt/surface.h>

//Include Headers
#include <vkdt/_pObjects.h>

vkdt::surface::surface::surface(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vulkan Surface Pointer
	vkdt::_pObjects::pVKSurface = &this -> vkdtVKSurface;

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT Surface!\n";
	}
}

vkdt::surface::surface::~surface()
{
	//Destroy Vulkan Surface
	vkDestroySurfaceKHR(*vkdt::_pObjects::pVKInstance, this -> vkdtVKSurface, this -> pAllocator);

	//Debug Destruction Success
	if(this -> verbose)
	{
		std::cout << "Successfully Destroyed VKDT Surface!\n";
	}
}

void vkdt::surface::surface::createVKDTSurface(VkAllocationCallbacks* allocator)
{
	//Create Vulkan Window Surface
	const VkResult createVulkanWindowSurfaceResult = glfwCreateWindowSurface
	(
		*vkdt::_pObjects::pVKInstance,
		*vkdt::_pObjects::pGLFWWindow,
		allocator,
		&this -> vkdtVKSurface
	);

	if(createVulkanWindowSurfaceResult == VK_SUCCESS)
	{
		//Debug Creation Success
		if(this -> debug || this -> verbose)
		{
			std::cout << "Successfully Created VKDT Surface!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Surface Error: " + std::to_string(createVulkanWindowSurfaceResult) + "!\n");
	}
}