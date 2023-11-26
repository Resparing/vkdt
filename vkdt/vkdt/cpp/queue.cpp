//Include Header File
#include <vkdt/queue.h>

//Include Headers
#include <_vkdt/pObjects.h>

vkdt::queue::queue::queue(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vulkan Graphics & Present Queue Pointers
	_vkdt::pObjects::pVKGraphicsQueue = &this -> vkdtVKGraphicsQueue;
	_vkdt::pObjects::pVKPresentQueue = &this -> vkdtVKPresentQueue;

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized & Setup VKDT Instance!\n";
	}
}

vkdt::queue::queue::~queue()
{
	//Debug Destruction Success
	if(this -> verbose)
	{
		std::cerr << "Deletion Function not Required VKDT Queue!\n";
	}
}