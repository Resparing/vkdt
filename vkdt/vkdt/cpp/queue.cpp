//Include Header File
#include <vkdt/queue.h>

//Include Headers
#include <_vkdt/pObjects.h>

vkdt::queue::queue::queue(const bool debug, const bool verbose) : debug(debug), verbose(verbose)
{
	//Set Vulkan Graphics & Present Queue Pointers
	vkdt::_pObjects::pVKGraphicsQueue = &this -> vkdtVKGraphicsQueue;
	vkdt::_pObjects::pVKPresentQueue = &this -> vkdtVKPresentQueue;

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