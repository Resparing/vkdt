//Include Header File
#include <vkdt/device.h>

//Include Headers
#include <_vkdt/pObjects.h>
#include <_vkdt/queueFamily.h>

vkdt::device::device::device
(
	const std::vector<const char*>& vkdtVKRequestedExtensions,
	const std::vector<const char*>& vkdtVKRequestedLayers,
	const bool debug,
	const bool verbose
) noexcept : vkdtVKLayers(vkdtVKRequestedLayers), vkdtVKExtensions(vkdtVKRequestedExtensions), debug(debug), verbose(verbose)
{
	//Set Vulkan Logical Device Pointer
	_vkdt::pObjects::pVKLogicalDevice = &this -> vkdtVKLogicalDevice;

	//Set Vulkan Extensions & Vulkan Layers
	if(this -> debug || this -> verbose)
	{
		//Add Validation Layers
		this -> vkdtVKLayers.push_back("VK_LAYER_KHRONOS_validation");
	}

	//Add Vulkan Swapchain Extension if Needed
	if(_vkdt::pObjects::pVKSurface)
	{
		this -> vkdtVKExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

		//Debug Addition Success
		if(this -> verbose)
		{
			std::cout << "Successfully Added Required Swapchain Extension: \"" << VK_KHR_SWAPCHAIN_EXTENSION_NAME << "\"!\n";
		}
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

		std::cout << "Added VKDT Vulkan Layers (" << this -> vkdtVKLayers.size() << "):\n";

		for(const char* vkdtVKLayer : this -> vkdtVKLayers)
		{
			std::cout << "\t\"" << vkdtVKLayer << "\"\n";
		}

		//Get GPU Name
		VkPhysicalDeviceProperties vkdtVKPhysicalDeviceProperties;
		vkGetPhysicalDeviceProperties(*_vkdt::pObjects::pVKPhysicalDevice, &vkdtVKPhysicalDeviceProperties);

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

	//Debug Deletion Success
	if(this -> verbose)
	{
		std::cout << "Successfully Destroyed VKDT Device!\n";
	}
}

void vkdt::device::device::createVKDTDevice(VkAllocationCallbacks* allocator)
{
	//Set Allocation Callback
	this -> pAllocator = allocator;

	//Find Queue Family Indexes
	_vkdt::queueFamily::Indices vkdtQueueFamilyIndexes = _vkdt::queueFamily::findQueueFamilyIndices(*_vkdt::pObjects::pVKPhysicalDevice);

	//Vector of Vulkan Queue Creation Information Structs
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = {};

	//Set of Unique Queue Families to Create
	std::set<uint32_t> vkdtVKUniqueQueueFamilyIndexes =
	{
		vkdtQueueFamilyIndexes.vkdtVKGraphicsFamily.value(),
		vkdtQueueFamilyIndexes.vkdtVKPresentFamily.value()
	};

	//Queue Priority - Between 0.0f & 1.0f
	float vkdtVKQueuePriority = 1.0f;

	//Iterate Over Vulkan Unique Queue Family Indexes to Fill Creation Information Struct
	for(uint32_t vkdtVKUniqueQueueFamilyIndex : vkdtVKUniqueQueueFamilyIndexes)
	{
		//Vulkan Queue Family Creation Information Struct
		VkDeviceQueueCreateInfo queueCreateInfo =
		{
			//Struct Type
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,

			//Vulkan Queue Family Index, Priority & Count
			.queueFamilyIndex = vkdtVKUniqueQueueFamilyIndex,
			.queueCount = 1,
			.pQueuePriorities = &vkdtVKQueuePriority,
		};

		queueCreateInfos.push_back(queueCreateInfo);
	}

	//Vulkan Physical Device Features Creation Information Struct
	VkPhysicalDeviceFeatures deviceFeatures = {};

	//Vulkan Logical Device Features Creation Information Struct
	VkDeviceCreateInfo logicalDeviceCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,

		//Pointer & Number of Vulkan Device Creation Information Struct
		.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
		.pQueueCreateInfos = queueCreateInfos.data(),

		//Pointer to Vulkan Device Feature Struct
		.pEnabledFeatures = &deviceFeatures,

		//Vulkan Extensions
		.enabledExtensionCount = static_cast<uint32_t>(this -> vkdtVKExtensions.size()),
		.ppEnabledExtensionNames = this -> vkdtVKExtensions.data(),

		//Vulkan Layers
		.enabledLayerCount = static_cast<uint32_t>(this -> vkdtVKLayers.size()),
		.ppEnabledLayerNames = this -> vkdtVKLayers.data(),
	};

	//Create Vulkan Logical Device
	const VkResult vkdtVKCreateDeviceResult = vkCreateDevice
	(
		*_vkdt::pObjects::pVKPhysicalDevice,
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
			vkGetPhysicalDeviceProperties(*_vkdt::pObjects::pVKPhysicalDevice, &vkdtVKDeviceInformation);

			std::cout																						\
			<< "Successfully Created VKDT Device from: \"" << vkdtVKDeviceInformation.deviceName			\
			<< "\" With: " << this -> vkdtVKExtensions.size() << " Extensions "								\
			<< "and: " << this -> vkdtVKLayers.size() << " Layers!\n";
		}

		else if(this -> debug)
		{
			std::cout << "Successfully Created VKDT Device!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Logical Device! Error: " + std::to_string(vkdtVKCreateDeviceResult) + "!\n");
	}

	//Get VKDT Device Queue
	vkGetDeviceQueue
	(
		this -> vkdtVKLogicalDevice,
		vkdtQueueFamilyIndexes.vkdtVKGraphicsFamily.value(),
		0,
		_vkdt::pObjects::pVKGraphicsQueue
	);

	//Get VKDT Device Queue
	vkGetDeviceQueue
	(
		this -> vkdtVKLogicalDevice,
		vkdtQueueFamilyIndexes.vkdtVKPresentFamily.value(),
		0,
		_vkdt::pObjects::pVKPresentQueue
	);
}