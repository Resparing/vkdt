//Include Header File
#include <vkdt/device.h>

//Include Headers
#include <vkdt/_pVKObjects.h>
#include <vkdt/_QueueFamily.h>

vkdt::device::device::device
(
	const std::vector<const char*>& vkdtVKRequestedExtensions,
	const std::vector<const char*>& vkdtVKRequestedLayers,
	const bool debug,
	const bool verbose
) noexcept : vkdtVKLayers(vkdtVKRequestedLayers), vkdtVKExtensions(vkdtVKRequestedExtensions), debug(debug), verbose(verbose)
{
	//Set Vulkan Logical Device Pointer
	vkdt::_pVKObjects::pVKLogicalDevice = &this -> vkdtVKLogicalDevice;

	//Set Vulkan Extensions & Vulkan Layers
	if(this -> debug || this -> verbose)
	{
		//Add Validation Layers
		this -> vkdtVKLayers.push_back("VK_LAYER_KHRONOS_validation");
	}

#ifdef __APPLE__

	//Add Required MacOS Vulkan Portability Subset & Flags
	this -> vkdtVKExtensions.push_back("VK_KHR_portability_subset");

	//Debug Addition of MacOS Extension
	if(this -> verbose)
	{
		std::cout << "Added Required MacOS Extension: \"" << "VK_KHR_portability_subset" << "\"!\n";
	}

#endif

	//Debug Initialization Success
	if(this -> verbose)
	{
		//Debug Requested Requested Vulkan Extensions & Layers
		std::cout << "Added VKDT Vulkan Extensions (" << this -> vkdtVKExtensions.size() << "):\n";

		for(const char* vkdtVKExtension : this -> vkdtVKExtensions)
		{
			std::cout << "\t\"" << vkdtVKExtension << "\"\n";
		}

		std::cout << "Added Vulkan Vulkan Layers (" << this -> vkdtVKLayers.size() << "):\n";

		for(const char* vkdtVKLayer : this -> vkdtVKLayers)
		{
			std::cout << "\t\"" << vkdtVKLayer << "\"\n";
		}

		//Get GPU Name
		VkPhysicalDeviceProperties vkdtVKPhysicalDeviceProperties;
		vkGetPhysicalDeviceProperties(*vkdt::_pVKObjects::pVKPhysicalDevice, &vkdtVKPhysicalDeviceProperties);

		std::cout																							\
		<< "Successfully Initialized VKDT Device with"														\
		<< " VKDT GPU: \"" << vkdtVKPhysicalDeviceProperties.deviceName << "\"!\n";
	}

	else if(this -> debug)
	{
		std::cout << "Successfully Initialized VKDT Device with Selected VKDT GPU!\n";
	}
}

vkdt::device::device::~device()
{
	//Destroy Vulkan Logical Device
	vkDestroyDevice(this -> vkdtVKLogicalDevice, this -> pAllocator);

	//Debug Destruction Success
	if(this -> verbose)
	{
		std::cout << "Successfully Destroyed VKDT Device!\n";
	}
}

void vkdt::device::device::createVKDTDevice(vkdt::queue::queue* vkdtGraphicsQueue, VkAllocationCallbacks* allocator)
{
	//Set Allocation Callback
	this -> pAllocator = allocator;

	//Find Queue Family Indexes
	vkdt::_QueueFamily::Indices vkdtQueueFamilyIndexes = vkdt::_QueueFamily::findQueueFamilyIndices(*vkdt::_pVKObjects::pVKPhysicalDevice);

	//Queue Priority - Between 0.0f & 1.0f
	float vkdtVKQueuePriority = 1.0f;

	//Vulkan Queue Family Creation Information Struct
	VkDeviceQueueCreateInfo queueCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,

		//Vulkan Queue Family Index, Priority & Count
		.queueFamilyIndex = vkdtQueueFamilyIndexes.vkdtVKGraphicsFamily.value(),
		.queueCount = 1,
		.pQueuePriorities = &vkdtVKQueuePriority,
	};

	//Vulkan Physical Device Features Creation Information Struct
	VkPhysicalDeviceFeatures deviceFeatures = {};

	//Vulkan Logical Device Features Creation Information Struct
	VkDeviceCreateInfo logicalDeviceCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,

		//Pointer & Number of Vulkan Device Creation Information Struct
		.pQueueCreateInfos = &queueCreateInfo,
		.queueCreateInfoCount = 1,

		//Pointer to Vulkan Device Feature Struct
		.pEnabledFeatures = &deviceFeatures,

		//Vulkan Extensions
		.enabledExtensionCount = static_cast<uint32_t>(this -> vkdtVKExtensions.size()),
		.ppEnabledExtensionNames = this -> vkdtVKExtensions.data(),

		//Vulkan Layers
		.enabledLayerCount = static_cast<uint32_t>(this -> vkdtVKLayers.size()),
		.ppEnabledLayerNames = this -> vkdtVKLayers.data(),
	};

	//Create VKDT Vulkan Logical Device
	const VkResult vkdtVKCreateDeviceResult = vkCreateDevice
	(
		*vkdt::_pVKObjects::pVKPhysicalDevice,
		&logicalDeviceCreateInfo,
		this -> pAllocator,
		&this -> vkdtVKLogicalDevice
	);

	if(vkdtVKCreateDeviceResult == VK_SUCCESS)
	{
		//Debug VKDT Device Creation Success
		if(this -> verbose)
		{
			//Get VKDT GPU Information
			VkPhysicalDeviceProperties vkdtVKDeviceInformation;
			vkGetPhysicalDeviceProperties(*vkdt::_pVKObjects::pVKPhysicalDevice, &vkdtVKDeviceInformation);

			std::cout																						\
			<< "Successfully Created VKDT Vulkan Device from: \"" << vkdtVKDeviceInformation.deviceName		\
			<< "\" With: " << this -> vkdtVKExtensions.size() << " Extensions "								\
			<< "and: " << this -> vkdtVKLayers.size() << " Layers!\n";
		}

		else if(this -> debug)
		{
			std::cout << "Successfully Create VKDT Vulkan Device!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Vulkan Logical Device! Error: " + std::to_string(vkdtVKCreateDeviceResult) + "!\n");
	}

	//Get VKDT Queue's
	vkGetDeviceQueue
	(
		this -> vkdtVKLogicalDevice,
		vkdtQueueFamilyIndexes.vkdtVKGraphicsFamily.value(),
		0,
		const_cast<VkQueue*>(&vkdtGraphicsQueue -> refVKQueue())
	);
}