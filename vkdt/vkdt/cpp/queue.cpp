//Include Header File
#include <vkdt/queue.h>

//Include Headers

vkdt::queue::queue::queue(const bool debug, const bool verbose) : debug(debug), verbose(verbose)
{

}

const VkQueue& vkdt::queue::queue::refVKQueue(void) const noexcept
{
    return this -> vkdtVKQueue;
}

vkdt::queue::queue::~queue()
{

}