//Include Header File
#include <vkdt/surface.h>

//Include Headers
#include <_vkdt/pObjects.h>

vkdt::surface::surface::surface(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vulkan Surface Pointer
	_vkdt::pObjects::pVKSurface = &this -> vkdtVKSurface;

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT Surface!\n";
	}
}

vkdt::surface::surface::~surface()
{
	//Destroy Vulkan Surface
	vkDestroySurfaceKHR(*_vkdt::pObjects::pVKInstance, this -> vkdtVKSurface, this -> pAllocator);

	//Debug Deletion Success
	if(this -> verbose)
	{
		std::cout << "Successfully Destroyed VKDT Surface!\n";
	}
}

void vkdt::surface::surface::createVKDTSurface(VkAllocationCallbacks* allocator)
{
	//Create Vulkan Window Surface
	const VkResult createVKWindowSurfaceResult = glfwCreateWindowSurface
	(
		*_vkdt::pObjects::pVKInstance,
		*_vkdt::pObjects::pGLFWWindow,
		allocator,
		&this -> vkdtVKSurface
	);

	if(createVKWindowSurfaceResult == VK_SUCCESS)
	{
		//Debug Creation Success
		if(this -> debug || this -> verbose)
		{
			std::cout << "Successfully Created VKDT Surface!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Surface Error: " + std::to_string(createVKWindowSurfaceResult) + "!\n");
	}
}