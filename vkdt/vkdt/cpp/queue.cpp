//Include Header File
#include <vkdt/queue.h>

//Include Headers
#include <_vkdt/pObjects.h>

vkdt::queue::queue::queue(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vulkan Graphics, Present Queue & Class Pointers
	_vkdt::pObjects::pVKGraphicsQueue = &this -> vkdtVKGraphicsQueue;
	_vkdt::pObjects::pVKPresentQueue = &this -> vkdtVKPresentQueue;
	_vkdt::pObjects::pVKDTQueue = this;

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized & Setup VKDT Instance!\n";
	}
}

vkdt::queue::queue::~queue()
{
	//Debug Deletion Success
	if(this -> verbose)
	{
		std::cerr << "Deletion Function not Required VKDT Queue!\n";
	}
}