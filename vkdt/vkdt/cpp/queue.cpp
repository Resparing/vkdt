//Include Header File
#include <vkdt/queue.h>

//Include Headers

vkdt::queue::queue::queue(const bool debug, const bool verbose) : debug(debug), verbose(verbose)
{

}

vkdt::queue::queue::~queue()
{

}

const VkQueue& vkdt::queue::queue::refVKQueue(void) const noexcept
{
	return this -> vkdtVKQueue;
}