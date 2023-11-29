//Include Header File
#include <vkdt/GPU.h>

//Include Headers
#include <_vkdt/pObjects.h>
#include <_vkdt/queueFamily.h>
#include <_vkdt/swapSupportDetail.h>

vkdt::GPU::GPU::GPU(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Vulkan Physical Device Pointer
	_vkdt::pObjects::pVKPhysicalDevice = &this -> vkdtVKPhysicalDevice;

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
	//Get Vector of Available Vulkan Physical Devices
	uint32_t vkdtVKAvailablePhysicalDeviceCount{};  //Number of Vulkan Physical Devices

	const VkResult vkdtVKPhysicalDeviceNumberResult = vkEnumeratePhysicalDevices
	(
		*_vkdt::pObjects::pVKInstance,
		&vkdtVKAvailablePhysicalDeviceCount,
		nullptr
	);

	if(vkdtVKPhysicalDeviceNumberResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find Number of VKDT GPU's! Error: " +
			std::to_string(vkdtVKAvailablePhysicalDeviceCount) +
			"!\n"
		);
	}

	//Vector of Available Physical Devices
	std::vector<VkPhysicalDevice> vkAvailablePhysicalDevices(vkdtVKAvailablePhysicalDeviceCount);

	const VkResult vkdtVKPhysicalDevicesResult = vkEnumeratePhysicalDevices
	(
		*_vkdt::pObjects::pVKInstance,
		&vkdtVKAvailablePhysicalDeviceCount,
		vkAvailablePhysicalDevices.data()
	);

	if(vkdtVKPhysicalDevicesResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find VKDT GPU's! Error: " + std::to_string(vkdtVKPhysicalDevicesResult) + "!\n");
	}

	//Check if Vulkan Physical Devices Available
	if(vkdtVKAvailablePhysicalDeviceCount == 0)
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
		std::cout << "Available VKDT GPU's (" << vkdtVKAvailablePhysicalDeviceCount << "):\n";

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
		std::cout << "Found: " << vkdtVKAvailablePhysicalDeviceCount << " GPU's!\n";
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

				std::cout << "Chose: \"" << vkdtVKDeviceInformation.deviceName << "\" as VKDT Physical Device!\n";
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

bool vkdt::GPU::GPU::checkPhysicalDeviceExtensionSupport(const VkPhysicalDevice& vkdtVKSelectedPhysicalDevice) const
{
	//Get Vulkan Physical Device Extensions
	uint32_t vkdtVKDeviceExtensionCount{};

	//Get Number of Vulkan Physical Device Extensions
	const VkResult vkdtVKPhysicalDeviceExtensionsCountResult = vkEnumerateDeviceExtensionProperties
	(
		vkdtVKSelectedPhysicalDevice,
		nullptr,
		&vkdtVKDeviceExtensionCount,
		nullptr
	);

	if(vkdtVKPhysicalDeviceExtensionsCountResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find Number of VKDT Vulkan Device Extensions! Error: " +
			std::to_string(vkdtVKPhysicalDeviceExtensionsCountResult) +
			"!\n"
		);
	}

	std::vector<VkExtensionProperties> vkdtVKAvailableDeviceExtensions(vkdtVKDeviceExtensionCount);

	const VkResult vkdtVKPhysicalDeviceCountResult = vkEnumerateDeviceExtensionProperties
	(
		vkdtVKSelectedPhysicalDevice,
		nullptr,
		&vkdtVKDeviceExtensionCount,
		vkdtVKAvailableDeviceExtensions.data()
	);

	if(vkdtVKPhysicalDeviceCountResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find VKDT Vulkan Device Extensions! Error: " +
			std::to_string(vkdtVKPhysicalDeviceCountResult) + "!\n"
		);
	}

	//Check if Swapchain Extension in VKDT Available Device Extensions
	for(const VkExtensionProperties& vkdtVKAvailableDeviceExtension : vkdtVKAvailableDeviceExtensions)
	{
		if(strcmp(vkdtVKAvailableDeviceExtension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0)
		{
			//Debug Finding Success
			if(this -> verbose)
			{
				std::cout << "Successfully Found VKDT Vulkan Swapchain Extension!\n";
			}

			//All Tests Have Passed
			return true;
		}
	}

	//Requested Extension was not Found
	if(this -> debug || this -> verbose)
	{
		std::cerr << "Couldn't Find VKDT Vulkan Swapchain Extension!\n";
	}

	return false;
}

bool vkdt::GPU::GPU::isVKDTGPUSuitable(const VkPhysicalDevice& vkdtVKSelectedPhysicalDevice) const noexcept
{
	//Get Index of Queue Family
	const struct _vkdt::queueFamily::Indices indexes = _vkdt::queueFamily::findQueueFamilyIndices
	(
		vkdtVKSelectedPhysicalDevice,
		this -> debug,
		this -> verbose
	);

	const bool vkdtVKExtensionsSupported = this -> checkPhysicalDeviceExtensionSupport(vkdtVKSelectedPhysicalDevice);

	//Figure out if Vulkan Swapchain is Supported
	bool vkdtVKSwapchainSupported{};

	if(vkdtVKExtensionsSupported)
	{
		//Get Struct of VKDT Vulkan Swapchain Support Details
		const struct _vkdt::swapSupportDetails::swapchainSupportDetails vkdtVKSwapchainSupport =		\
		_vkdt::swapSupportDetails::queueSwapChainSupport(vkdtVKSelectedPhysicalDevice);

		//Check if Vulkan Swapchain is Supported
		vkdtVKSwapchainSupported = !vkdtVKSwapchainSupport.vkdtVKPresentModes.empty() && !vkdtVKSwapchainSupport.vkdtVKSurfaceFormats.empty();
	}

	//Return if Vulkan has Value
	return indexes.isComplete() && vkdtVKExtensionsSupported && vkdtVKSwapchainSupported;
}