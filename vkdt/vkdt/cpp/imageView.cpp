//Include Header File
#include <vkdt/imageView.h>

//Include Headers
#include <_vkdt/pObjects.h>

vkdt::imageView::imageView::imageView(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vector of Vulkan Swapchain Images & Image View
	_vkdt::pObjects::pSwapImages = &this -> vkdtVKSwapchainImages;
}

vkdt::imageView::imageView::~imageView()
{

}