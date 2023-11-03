//Include Header File
#include <vkdt/_QueueFamily.h>

//Include Headers

bool vkdt::_QueueFamily::Indices::isComplete(void) const noexcept
{
    return this -> vkdtVKGraphicsFamily.has_value();
}

struct vkdt::_QueueFamily::Indices vkdt::_QueueFamily::findQueueFamilyIndices
(
    const VkPhysicalDevice& vkdtVKPhysicalDevice,
    const bool debug,
    const bool verbose
) noexcept
{
    //Struct of Vulkan Queue Family Indexes
    struct _QueueFamily::Indices indices;

    //Get Vulkan Queue Family Indexes
    uint32_t vkQueueFamilyCount{};  //Number of VKDT Vulkan Queue Family Indexes
    vkGetPhysicalDeviceQueueFamilyProperties(vkdtVKPhysicalDevice, &vkQueueFamilyCount, nullptr);  //Get Number of Queue Family Indexes
    std::vector<VkQueueFamilyProperties> vkQueueFamilies(vkQueueFamilyCount);  //Vector of Vulkan Queue Family Properties
    vkGetPhysicalDeviceQueueFamilyProperties(vkdtVKPhysicalDevice, &vkQueueFamilyCount, vkQueueFamilies.data());  //Query Properties Again

    //Debug Number of Vulkan Queue Family Indexes
    if(debug || verbose)
    {
        std::cout << "Found: " << vkQueueFamilyCount << " Queue Families!\n";
    }

    //Iterate Over Vulkan Queue Families
    for(size_t i = 0; i < vkQueueFamilies.size(); ++i)
    {
        //Check if Selected Queue Family Supports Graphics Queue
        if(vkQueueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            if(verbose)
            {
                //Debug Queue Family Found Success
                std::cout << "Successfully Found Available Queue Family at Index: " << i << "!\n";

            }

            //Set Graphics Family Index
            indices.vkdtVKGraphicsFamily = i;
        }

        if(indices.isComplete())
        {
            break;
        }
    }

    return indices;
}