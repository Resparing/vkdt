//Include Header File
#include <vkdt/instance.h>

//Include Headers
#include <vkdt/debug.h>
#include <vkdt/_pObjects.h>

vkdt::instance::instance::instance
(
	const struct vkdt::instance::envVariables& macEnvVariables,
	const vkdt::instance::applicationData& applicationInfo,
	const bool debug,
	const bool verbose
) : macOSEnvVariables(macEnvVariables), appData(applicationInfo), debug(debug), verbose(verbose)
{
	//Set Vulkan Instance Pointer
	vkdt::_pObjects::pVKInstance = &this -> vkdtVKInstance;

	//Debug VKDT Instance Information
	if(verbose)
	{
		std::cout																					\
		<< "Successfully Received Application Information With"							 			\
		<< " Name: \"" << this -> appData.name														\
		<< "\" Version: Patch " << this -> appData.version.patch									\
		<< ", Major " << this -> appData.version.major												\
		<< ", Minor " << this -> appData.version.minor												\
		<< ". Variant: " << this -> appData.version.variant << "!\n";
	}

	else if(this -> debug)
	{
		std::cout																					\
		<< "Successfully Received Application Information With"							 			\
		" Name: \"" << this -> appData.name												 			\
		<< "\", Version: " << this -> appData.version.patch								 			\
		<< "." << this -> appData.version.major											 			\
		<< "." << this -> appData.version.minor											 			\
		<< "." << this -> appData.version.variant << "!\n";
	}

#ifdef __APPLE__

	//Check if MacOS Environment Variables Struct is Initialized
	if(this -> macOSEnvVariables.VK_ICD_FILENAMES.empty() || this -> macOSEnvVariables.VK_LAYER_PATH.empty())
	{
		return;
	}

	//Set MoltenVK Required Environment Variable
	if(setenv("VK_ICD_FILENAMES", this -> macOSEnvVariables.VK_ICD_FILENAMES.c_str(), 0) == 0)
	{
		//Debug Success
		if(this -> verbose)
		{
			std::cout																				\
			<< "Successfully Set: \"" << "VK_ICD_FILENAMES"											\
			<< "\" Environment Variable as: \"" << this -> macOSEnvVariables.VK_ICD_FILENAMES << "\"!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Set: \"VK_ICD_FILENAMES\" Environment Variable!\n");
	}

	//Set Vulkan Layer(s) Required Environment Variables
	if(setenv("VK_LAYER_PATH", this -> macOSEnvVariables.VK_LAYER_PATH.c_str(), 0) == 0)
	{
		//Debug Success
		if(this -> verbose)
		{
			std::cout																				\
			<< "Successfully Set: \"" << "VK_LAYER_PATH"											\
			<< "\" Environment Variable as: \"" << this -> macOSEnvVariables.VK_LAYER_PATH << "\"!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Set: \"VK_LAYER_PATH\" Environment Variable!\n");
	}

#else

	//Vulkan Environment Variables Not Needed
	if(this -> macOSEnvVariables)
	{
		throw std::runtime_error("Vulkan Environment Variables not Needed, Required by MacOS Only!\n");
	}

#endif
}

vkdt::instance::instance::~instance()
{
	//Destroy Vulkan Instance
	vkDestroyInstance(this -> vkdtVKInstance, this -> pAllocator);

	if(this -> verbose)
	{
		//Debug Deletion Success
		std::cout << "Successfully Destroyed VKDT Instance!\n";
	}
}

void vkdt::instance::instance::setupVKDTInstance
(
	const std::vector<const char*>& vkdtRequestedExtensions,
	const std::vector<const char*>& vkdtRequestedLayers
)
{
	//Add Required GLFW Extensions
	std::uint32_t vkdtGLFWExtensionCount{};  //Number of Extensions
	const char** vkdtGLFWExtensions{};  //Names of Extensions
	vkdtGLFWExtensions = glfwGetRequiredInstanceExtensions(&vkdtGLFWExtensionCount);  //Get GLFW Required Extensions

	//Check if Vulkan Extensions are Requested
	if(vkdtGLFWExtensions == NULL)
	{
		throw std::runtime_error("Required GLFW Vulkan Extensions not Found! (Did you Setup Vulkan Correctly?)\n");
	}

	//Debug Required GLFW Extensions
	if(this -> verbose)
	{
		std::cout << "Added Required GLFW Extensions (" << vkdtGLFWExtensionCount << "):\n";

		for(size_t i{}; i < static_cast<size_t>(vkdtGLFWExtensionCount); ++i)
		{
			std::cout << "\t[" << i << "] \"" << vkdtGLFWExtensions[i] << "\"\n";
		}
	}

	else if(this -> debug)
	{
		std::cout << "Added: " << vkdtGLFWExtensionCount << " Required GLFW Extensions!\n";
	}

	//Add GLFW Extensions to VKDT Extensions
	for(size_t i{}; i < static_cast<size_t>(vkdtGLFWExtensionCount); ++i)
	{
		vkdtExtensions.push_back(vkdtGLFWExtensions[i]);
	}

	//Add VKDT Vulkan Debugging Extensions & Layers
	if(this -> debug || this -> verbose)
	{
		//Add Debugging Extensions & Layers to Vectors
		this -> vkdtLayers.push_back("VK_LAYER_KHRONOS_validation");
		this -> vkdtExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		//Debug Information
		if(this -> verbose)
		{
			std::cout																				\
			<< "Added Required Debugging Software: \"" << "VK_LAYER_KHRONOS_validation"	 			\
			<< "\" and: \"" << VK_EXT_DEBUG_UTILS_EXTENSION_NAME << "\"!\n";
		}
	}

#ifdef __APPLE__

	//Add Required MacOS Extension & Flags
	this -> vkdtExtensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	this -> vkdtVKInstanceCreateInfoFlags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

	//Debug Required Added Extension
	if(this -> verbose)
	{
		std::cout << "Added Required MacOS Vulkan Extension: \"" << VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME << "\"!\n";
	}

#endif

	//Add Requested VKDT Extensions & Layers
	this -> vkdtExtensions.insert(this -> vkdtExtensions.end(), vkdtRequestedExtensions.begin(), vkdtRequestedExtensions.end());
	this -> vkdtLayers.insert(this -> vkdtLayers.end(), vkdtRequestedLayers.begin(), vkdtRequestedLayers.end());

	//Debug Requested VKDT Extensions
	if(this -> verbose)
	{
		//Debug Requested Extensions - At Least Contains VK_KHR_surface Extension
		std::cout << "Added Requested VKDT Vulkan Extensions (" << this -> vkdtExtensions.size() << "):\n";

		for(const char* vkdtExtension : this -> vkdtExtensions)
		{
			std::cout << "\t\"" << vkdtExtension << "\"\n";
		}

		//No Vulkan Layers Requested
		if(this -> vkdtLayers.size() > 0)
		{
			//Debug Requested Layers
			std::cout << "Added Requested VKDT Vulkan Layers (" << this -> vkdtLayers.size() << "):\n";

			for(const char* vkdtLayer : this -> vkdtLayers)
			{
				std::cout << "\t\"" << vkdtLayer << "\"\n";
			}
		}
	}

	else if(this -> debug)
	{
		std::cout << "Added: " << this -> vkdtExtensions.size() << " VKDT Vulkan Extensions!\n";
		std::cout << "Added: " << this -> vkdtLayers.size() << " VKDT Vulkan Layers!\n";
	}
}

void vkdt::instance::instance::createVKDTInstance(VkAllocationCallbacks* allocator)
{
	//Set Allocator
	this -> pAllocator = allocator;

	//Find Vulkan Instance Version
	uint32_t vkdtVkInstanceVersion{};

	//Get Vulkan Instance Version
	const VkResult vkdtVkInstanceVersionResult = vkEnumerateInstanceVersion(&vkdtVkInstanceVersion);

	if(vkdtVkInstanceVersionResult != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find Supported Vulkan Version! Error: " + std::to_string(vkdtVkInstanceVersionResult) + "!\n");
	}

	//Debug Available Version
	if(this -> verbose)
	{
		std::cout																					\
		<< "Supporting Vulkan Version Patch: " << VK_API_VERSION_PATCH(vkdtVkInstanceVersion)		\
		<< ", Major " << VK_API_VERSION_MAJOR(vkdtVkInstanceVersion) 								\
		<< ", Minor " << VK_API_VERSION_MINOR(vkdtVkInstanceVersion)								\
		<< ". Variant: " << VK_API_VERSION_VARIANT(vkdtVkInstanceVersion) << "!\n";
	}

	else if(this -> debug)
	{
		std::cout	 																				\
		<< "Supporting Vulkan Version: " << VK_API_VERSION_PATCH(vkdtVkInstanceVersion)
		<< "." << VK_API_VERSION_MAJOR(vkdtVkInstanceVersion)
		<< "." << VK_API_VERSION_MINOR(vkdtVkInstanceVersion)
		<< "." << VK_API_VERSION_VARIANT(vkdtVkInstanceVersion) << "!\n";
	}

	//Vulkan Application Information Struct
	const VkApplicationInfo instanceAppInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,

		//Vulkan API Version
		.apiVersion = vkdtVkInstanceVersion,

		//Engine Information
		.pEngineName = "VKDT Engine",
		.engineVersion = vkdtVkInstanceVersion,

		//Application Information
		.pApplicationName = this -> appData.name.c_str(),
		.applicationVersion = VK_MAKE_API_VERSION													\
		(																							\
			this -> appData.version.variant,														\
			this -> appData.version.major,															\
			this -> appData.version.minor,															\
			this -> appData.version.patch															\
		),
	};

	//Vulkan Create Instance Information Struct
	VkInstanceCreateInfo instanceCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,

		//Pointer to Vulkan Application Information Struct
		.pApplicationInfo = &instanceAppInfo,

		//Vulkan Instance Extensions
		.enabledExtensionCount = static_cast<uint32_t>(this -> vkdtExtensions.size()),
		.ppEnabledExtensionNames = this -> vkdtExtensions.data(),

		//Vulkan Instance Layers
		.enabledLayerCount = static_cast<uint32_t>(this -> vkdtLayers.size()),
		.ppEnabledLayerNames = this -> vkdtLayers.data(),

		//Vulkan Flags
		.flags = vkdtVKInstanceCreateInfoFlags,
	};


	//Vulkan Debug Utils Messenger Creation Information Struct
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};

	//Add Debugging to Vulkan Instance Creation & Destruction Functions
	if(this -> verbose)
	{
		//Fil Vulkan Debug Utils Creation Information Struct
		vkdt::debug::messenger::fillDebugUtilsCreateInfo(debugCreateInfo);

		//Add Struct to Instance Creation Information Struct
		instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;

		//Debug Addition of Debug Utils Messenger Creation Information Struct
		if(this -> verbose)
		{
			std::cout << "Successfully Added Debugging Information to Vulkan Instance Creation Information Struct!\n";
		}
	}

	//Create Vulkan Instance
	const VkResult vkdtVkInstanceCreationResult = vkCreateInstance(&instanceCreateInfo, this -> pAllocator, &this -> vkdtVKInstance);
	if(vkdtVkInstanceCreationResult == VK_SUCCESS)
	{
		if(this -> verbose)
		{
			std::cout << "Successfully Created VKDT Instance Called: \"" << this -> appData.name << "\"!\n";
		}

		else if(this -> debug)
		{
			std::cout << "Successfully Created VKDT Instance!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Instance! Error: " + std::to_string(vkdtVkInstanceCreationResult) + "!\n");
	}
}

bool vkdt::instance::instance::requestedExtensionsSupported(void) const
{
	//Check Vulkan Extensions
	std::uint32_t vkdtVKAvailableExtensionCount{};

	const VkResult vkdtVkInstanceExtensionCountResult = vkEnumerateInstanceExtensionProperties
	(
		nullptr,
		&vkdtVKAvailableExtensionCount,
		nullptr
	);

	if(vkdtVkInstanceExtensionCountResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find Number of VKDT Vulkan Instance Extensions! Error: " +
			std::to_string(vkdtVkInstanceExtensionCountResult) + "!\n"
		);
	}

	std::vector<VkExtensionProperties> vkdtVKAvailableExtensions(vkdtVKAvailableExtensionCount);

	const VkResult vkdtVkInstanceExtensionsResult = vkEnumerateInstanceExtensionProperties
	(
		nullptr,
		&vkdtVKAvailableExtensionCount,
		vkdtVKAvailableExtensions.data()
	);

	if(vkdtVkInstanceExtensionsResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find VKDT Vulkan Instance Extensions! Error: " +
			std::to_string(vkdtVkInstanceExtensionsResult) + "!\n"
		);
	}

	//Debug Number of Vulkan Extensions
	if(this -> verbose)
	{
		std::cout << "Available VKDT Vulkan Extensions (" << vkdtVKAvailableExtensionCount << "):\n";

		for(const VkExtensionProperties& vkdtVKAvailableExtension : vkdtVKAvailableExtensions)
		{
			std::cout << "\t\"" << vkdtVKAvailableExtension.extensionName << "\"\n";
		}
	}
	else if(this -> debug)
	{
		std::cout << "Available VKDT Vulkan Extensions: " << vkdtVKAvailableExtensionCount << "!\n";
	}

	//Check if Requested Extensions are in VKDT Available Extensions
	for(const char* vkdtExtension : this -> vkdtExtensions)
	{
		bool isFound{};

		for(const VkExtensionProperties& vkdtVKAvailableExtension : vkdtVKAvailableExtensions)
		{
			if(strcmp(vkdtExtension, vkdtVKAvailableExtension.extensionName) == 0)
			{
				//Found Extension!
				isFound = true;

				if(this -> verbose)
				{
					std::cout << "Successfully Found VKDT Vulkan Extension: \"" << vkdtExtension << "\"!\n";
				}

				break;
			}
		}

		//Requested Extension was not Found
		if(!isFound)
		{
			if(this -> debug || this -> verbose)
			{
				std::cerr << "Unsuccessfully Tried to Find VKDT Vulkan Extension: \"" << vkdtExtension << "\"!\n";
			}

			return false;
		}
	}

	//All Tests Have Passed
	return true;
}

bool vkdt::instance::instance::requestedLayersSupported(void) const
{
	//Check Vulkan Layers
	std::uint32_t vkdtVKAvailableLayerCount{};

	const VkResult vkdtVkInstanceLayerCountResult = vkEnumerateInstanceLayerProperties(&vkdtVKAvailableLayerCount, nullptr);

	if(vkdtVkInstanceLayerCountResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find Number of VKDT Vulkan Instance Layer Properties! Error: " +
			std::to_string(vkdtVkInstanceLayerCountResult) + "!\n"
		);
	}

	std::vector<VkLayerProperties> vkdtVKAvailableLayers(vkdtVKAvailableLayerCount);

	const VkResult vkdtVkInstanceLayersResult = vkEnumerateInstanceLayerProperties(&vkdtVKAvailableLayerCount, vkdtVKAvailableLayers.data());

	if(vkdtVkInstanceLayersResult != VK_SUCCESS)
	{
		throw std::runtime_error
		(
			"Failed to Find VKDT Vulkan Instance Layers! Error: " +
			std::to_string(vkdtVkInstanceLayersResult) + "!\n"
		);
	}

	//Debug Number of Vulkan Layers
	if(this -> verbose)
	{
		std::cout << "Available VKDT Vulkan Layers (" << vkdtVKAvailableLayerCount << "):\n";

		for(const VkLayerProperties& vkdtVKAvailableLayer : vkdtVKAvailableLayers)
		{
			std::cout																				\
			<< "\t\"" << vkdtVKAvailableLayer.layerName									 			\
			<< "\": " << vkdtVKAvailableLayer.description << "\n";
		}
	}
	else if(this -> debug)
	{
		std::cout << "Available VKDT Vulkan Layers: " << vkdtVKAvailableLayerCount << "!\n";
	}

	//Check if Requested Layers are in VKDT Available Layers
	for(const char* vkdtLayer : this -> vkdtLayers)
	{
		bool isFound{};

		for(const VkLayerProperties& vkdtVKAvailableLayer : vkdtVKAvailableLayers)
		{
			if(strcmp(vkdtLayer, vkdtVKAvailableLayer.layerName) == 0)
			{
				//Found Layer!
				isFound = true;

				if(this -> verbose)
				{
					std::cout << "Successfully Found VKDT Vulkan Layer: \"" << vkdtLayer << "\"!\n";
				}

				break;
			}
		}

		//Requested Layer was not Found
		if(!isFound)
		{
			if(this -> debug || this -> verbose)
			{
				std::cerr << "Unsuccessfully Tried to Find VKDT Vulkan Layer: \"" << vkdtLayer << "\"!\n";
			}

			return false;
		}
	}

	//All Tests Have Passed
	return true;
}