//Include Header File
#include <vkdt/GPU.h>

//Include Headers
#include <vkdt/_pObjects.h>
#include <vkdt/_QueueFamily.h>

vkdt::GPU::GPU::GPU(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vulkan Physical Device Pointer
	vkdt::_pObjects::pVKPhysicalDevice = &this -> vkdtVKPhysicalDevice;

	//Debug GPU Creation Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT GPU!\n";
	}
}

vkdt::GPU::GPU::~GPU()
{
	if(this -> verbose)
	{
		std::cerr << "Delete Function not Required for VKDT GPU!\n";
	}
}

void vkdt::GPU::GPU::findVKDTGPU(const char* vkdtGPUName)
{
	//Get Vector of Available VKDT Vulkan Physical Devices
	uint32_t vkAvailablePhysicalDeviceCount{};  //Number of VKDT Vulkan Physical Devices

	const VkResult vkdtVkPhysicalDeviceNumberResult = vkEnumeratePhysicalDevices
	(
		*vkdt::_pObjects::pVKInstance,
		&vkAvailablePhysicalDeviceCount,
		nullptr
	);

	if(vkdtVkPhysicalDeviceNumberResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find Number of VKDT GPU's! Error: " + std::to_string(vkdtVkPhysicalDeviceNumberResult) + "!\n");
	}

	//Vector of Available Physical Devices
	std::vector<VkPhysicalDevice> vkAvailablePhysicalDevices(vkAvailablePhysicalDeviceCount);

	const VkResult vkdtVKPhysicalDevicesResult = vkEnumeratePhysicalDevices
	(
		*vkdt::_pObjects::pVKInstance,
		&vkAvailablePhysicalDeviceCount,
		vkAvailablePhysicalDevices.data()
	);

	if(vkdtVKPhysicalDevicesResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find VKDT GPU's! Error: " + std::to_string(vkdtVKPhysicalDevicesResult) + "!\n");
	}

	//Check if VKDT Vulkan Physical Devices Available
	if(vkAvailablePhysicalDeviceCount == 0)
	{
		if(this -> verbose)
		{
			std::cerr << "No Available VKDT GPU's Found!\n";
		}

		return;
	}

	//Debug Vulkan Physical Devices
	if(this -> verbose)
	{
		std::cout << "Available VKDT GPU's (" << vkAvailablePhysicalDeviceCount << "):\n";

		for(const VkPhysicalDevice& vkAvailablePhysicalDevice : vkAvailablePhysicalDevices)
		{
			//Find Vulkan Physical Device Name
			VkPhysicalDeviceProperties vkdtVKDeviceInformation;
			vkGetPhysicalDeviceProperties(vkAvailablePhysicalDevice, &vkdtVKDeviceInformation);

			//Debug GPU
			std::cout << "\t\"" << vkdtVKDeviceInformation.deviceName << "\"\n";
		}
	}

	else if(this -> debug)
	{
		std::cout << "Found: " << vkAvailablePhysicalDeviceCount << " GPU's!\n";
	}

	//Check if VKDT GPU Force Requested
	if(vkdtGPUName && strcmp("", vkdtGPUName) != 0)
	{
		for(const VkPhysicalDevice& vkAvailablePhysicalDevice : vkAvailablePhysicalDevices)
		{
			//Find Vulkan Physical Device Name
			VkPhysicalDeviceProperties vkdtVKDeviceInformation;
			vkGetPhysicalDeviceProperties(vkAvailablePhysicalDevice, &vkdtVKDeviceInformation);

			//Check if VKDT GPU is Found
			if(strcmp(vkdtVKDeviceInformation.deviceName, vkdtGPUName) == 0)
			{
				//VKDT GPU is Found!
				if(this -> debug || this -> verbose)
				{
					std::cout << "Successfully Found VKDT GPU: \"" << vkdtGPUName << "\"!\n";
				}

				this -> vkdtVKPhysicalDevice = vkAvailablePhysicalDevice;

				return;
			}
		}

		//No VKDT GPT Found
		throw std::runtime_error("Failed to Find VKDT GPU Requested!\n");
	}

	//Find Vulkan Physical Devices - Return First One With Specified Results
	for(const VkPhysicalDevice& vkAvailablePhysicalDevice : vkAvailablePhysicalDevices)
	{
		if(this -> isVKDTGPUSuitable(vkAvailablePhysicalDevice))
		{
			//Found Available Vulkan Physical Device
			if(this -> verbose)
			{
				//Find Vulkan Physical Device Name
				VkPhysicalDeviceProperties vkdtVKDeviceInformation;
				vkGetPhysicalDeviceProperties(vkAvailablePhysicalDevice, &vkdtVKDeviceInformation);

				std::cout << "Chose: \"" << vkdtVKDeviceInformation.deviceName << "\" as VKDT Vulkan Physical Device!\n";
			}

			//Set Vulkan Physical Device to Selected GPU
			this -> vkdtVKPhysicalDevice = vkAvailablePhysicalDevice;

			break;
		}
	}

	//Check if any Vulkan Physical Device is Selected
	if(this -> vkdtVKPhysicalDevice == VK_NULL_HANDLE)
	{
		throw std::runtime_error("Failed to Find & Select VKDT GPU!\n");
	}
}

bool vkdt::GPU::GPU::isVKDTGPUSuitable(const VkPhysicalDevice& vkdtVKSelectedPhysicalDevice) const noexcept
{
	//Get Index of Queue Family
	struct vkdt::_QueueFamily::Indices indexes = vkdt::_QueueFamily::findQueueFamilyIndices
	(
		vkdtVKSelectedPhysicalDevice,
		this -> debug,
		this -> verbose
	);

	//Return if Vulkan has Value
	return indexes.isComplete();
}