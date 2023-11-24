//Include Header File
#include <_vkdt/queueFamily.h>

//Include Headers
#include <_vkdt/pObjects.h>

bool vkdt::_QueueFamily::Indices::isComplete(void) const noexcept
{
	return this -> vkdtVKGraphicsFamily.has_value() && this -> vkdtVKPresentFamily.has_value();
}

struct vkdt::_QueueFamily::Indices vkdt::_QueueFamily::findQueueFamilyIndices
(
	const VkPhysicalDevice& vkdtVKPhysicalDevice,
	const bool debug,
	const bool verbose
)
{
	//Struct of Vulkan Queue Family Indexes
	struct _QueueFamily::Indices indices;

	//Get Vulkan Queue Family Indexes
	uint32_t vkQueueFamilyCount{};  //Number of Vulkan Queue Family Indexes
	vkGetPhysicalDeviceQueueFamilyProperties(vkdtVKPhysicalDevice, &vkQueueFamilyCount, nullptr);  //Get Number of Queue Family Indexes
	std::vector<VkQueueFamilyProperties> vkQueueFamilies(vkQueueFamilyCount);  //Vector of Vulkan Queue Family Properties
	vkGetPhysicalDeviceQueueFamilyProperties(vkdtVKPhysicalDevice, &vkQueueFamilyCount, vkQueueFamilies.data());  //Query Properties Again

	//Debug Number of Vulkan Queue Family Indexes
	if(debug || verbose)
	{
		std::cout << "Found: " << vkQueueFamilyCount << " Queue Families!\n";
	}

	//Iterate Over Vulkan Queue Families
	for(uint32_t i = 0; i < vkQueueFamilies.size(); ++i)
	{
		//Check if Selected Queue Family Supports Graphics Queue
		if(vkQueueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			if(verbose)
			{
				//Debug Queue Family Found Success
				std::cout << "Successfully Found Available Graphics Queue Family at Index: " << i << "!\n";

			}

			//Set Graphics Family Index
			indices.vkdtVKGraphicsFamily = i;
		}

		//Check Present Support of Selected Queue Family
		VkBool32 vkdtVKPresentSupport{};

		const VkResult vkdtVKGetPhysicalDeviceSupportResult = vkGetPhysicalDeviceSurfaceSupportKHR
		(
			vkdtVKPhysicalDevice,
			i,
			*vkdt::_pObjects::pVKSurface,
			&vkdtVKPresentSupport
		);

		if(vkdtVKGetPhysicalDeviceSupportResult != VK_SUCCESS)
		{
			throw std::runtime_error
			(
				"Failed to Find Vulkan Queue Family Present Support! Error: " +
				std::to_string(vkdtVKGetPhysicalDeviceSupportResult) + "!\n"
			);
		}

		if(vkdtVKPresentSupport)
		{
			if(verbose)
			{
				//Debug Queue Family Found Success
				std::cout << "Successfully Found Available Present Queue Family at Index: " << i << "!\n";

			}

			//Set Graphics Family Index
			indices.vkdtVKPresentFamily = i;
		}

		if(indices.isComplete())
		{
			break;
		}
	}

	return indices;
}