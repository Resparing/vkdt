//Include Header File
#include <vkdt/instance.h>

//Include Headers

/**
 * @brief Vulkan Needed Implementation of VKDT Callback
 *
 * @param messageSeverity Severity of Vulkan Message to Debug
 * @param messageType Type of Vulkan Message to Debug
 * @param pCallbackData Information on Vulkan Message to Debug
 * @param pUserData Optional Data
 *
 * @return VK_FALSE, Mandatory Return Statement
 */
static VKAPI_ATTR VkBool32 VKAPI_CALL vkdtVKDebugCallback
(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData
)
{
	//Check if User Data Contains Anything
	if(pUserData)
	{
		throw std::runtime_error("VKDT Vulkan Debug Callback Function Contains Invalid Information!\n");
	}

	//Call VKDT Debug Function
	vkdt::debug::vkdtCallbackFunc(messageSeverity, messageType, pCallbackData);

	//Mandatory Return Statement
	return VK_FALSE;
}

vkdt::instance::instance::instance
(
	const struct vkdt::instance::envVariables& macEnvVariables,
	const vkdt::instance::applicationData& applicationInfo,
	const bool debug,
	const bool verbose
) : macOSEnvVariables(macEnvVariables), appData(applicationInfo), debug(debug), verbose(verbose)
{
	//Debug VKDT Instance Information
	if(verbose)
	{
		std::cout																					\
		<< "Successfully Received Application Information With"							 			\
		<< " Name: \"" << this -> appData.name											  			\
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

	//Set MoltenVK Required Environment Variable
	if(this -> macOSEnvVariables.VK_ICD_FILENAMES && setenv("VK_ICD_FILENAMES", this -> macOSEnvVariables.VK_ICD_FILENAMES, 1) == 0)
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
	if(this -> macOSEnvVariables.VK_LAYER_PATH && setenv("VK_LAYER_PATH", this -> macOSEnvVariables.VK_LAYER_PATH, 1) == 0)
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

void vkdt::instance::instance::setupVKDTInstance
(
	const std::vector<const char*> vkdtRequestedExtensions,
	const std::vector<const char*> vkdtRequestedLayers
)
{
	//Add Required GLFW Extensions
	std::uint32_t vkdtGLFWExtensionCount{};  //Number of Extensions
	const char** vkdtGLFWExtensions{};  //Names of Extensions
	vkdtGLFWExtensions = glfwGetRequiredInstanceExtensions(&vkdtGLFWExtensionCount);  //Get GLFW Required Extensions

	//Check if Vulkan Extensions are Requested
	if(vkdtGLFWExtensions == NULL)
	{
		throw std::runtime_error("Required GLFW Vulkan Extensions not Found!\n");
	}

	//Debug Required GLFW Extensions
	if(this -> verbose)
	{
		std::cout << "Added Required GLFW Extensions (" << vkdtGLFWExtensionCount << "):\n";

		for(std::size_t i{}; i < static_cast<size_t>(vkdtGLFWExtensionCount); ++i)
		{
			std::cout << "\t[" << i << "] \"" << vkdtGLFWExtensions[i] << "\"\n";
		}
	}

	else if(this -> debug)
	{
		std::cout << "Added: " << vkdtGLFWExtensionCount << " Required GLFW Extensions!\n";
	}

	//Add GLFW Extensions to VKDT Extensions
	for(std::size_t i{}; i < static_cast<size_t>(vkdtGLFWExtensionCount); ++i)
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

void vkdt::instance::instance::createVKDTInstance(vkdt::debug::vkdtCallback callbackFunc, VkAllocationCallbacks* allocator)
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
		.pApplicationName = this -> appData.name,
		.applicationVersion = VK_MAKE_API_VERSION													\
		(																							\
			this -> appData.version.variant,														\
			this -> appData.version.major,												  			\
			this -> appData.version.minor,												  			\
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
		.flags  = vkdtVKInstanceCreateInfoFlags,
	};

	//Vulkan Debug Utils Messenger Creation Information Struct
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};

	//Add Debugging to Vulkan Instance Creation & Destruction Functions
	if(this -> verbose)
	{
		//Fil Vulkan Debug Utils Creation Information Struct
		this -> fillDebugUtilsCreateInfo(debugCreateInfo);

		//Set Callback Function
		vkdt::debug::vkdtCallbackFunc = callbackFunc;

		//Add Struct to Instance Creation Information Struct
		instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;

		//Debug Addition of Debug Utils Messenger Creation Information Struct
		if(this -> verbose)
		{
			std::cout << "Successfully Added Debugging Information to Vulkan Instance Creation Information!\n";
		}
	}

	//Create Vulkan Instance
	const VkResult vkdtVkInstanceCreationResult = vkCreateInstance(&instanceCreateInfo, this -> pAllocator, &this -> vkdtVKInstance);
	if(vkdtVkInstanceCreationResult == VK_SUCCESS)
	{
		if(this -> verbose)
		{
			std::cout << "Successfully Created VKDT Vulkan Instance Called: \"" << this -> appData.name << "\"!\n";
		}

		else if(this -> debug)
		{
			std::cout << "Successfully Created VKDT Vulkan Instance!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Vulkan Instance! Error: " + std::to_string(vkdtVkInstanceCreationResult) + "!\n");
	}
}

void vkdt::instance::instance::createVKDTDebugMessenger(void)
{
	//Stop if not Debugging
	if(this -> debug == false && this -> verbose == false)
	{
		return;
	}

	//Create & Fill Vulkan Debug Utils Creation Information Struct
	VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo = {};
	this -> fillDebugUtilsCreateInfo(debugMessengerCreateInfo);

	//Locate & Load Function to Create Vulkan Debug Utils Messenger
	const PFN_vkCreateDebugUtilsMessengerEXT createVKDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>
	(
		vkGetInstanceProcAddr
		(
			this -> vkdtVKInstance,
			"vkCreateDebugUtilsMessengerEXT"
		)
	);

	//Check if Function Created Successfully
	if(!createVKDebugUtilsMessengerEXT)
	{
		throw std::runtime_error("Failed to Locate & Load VKDT Vulkan Debug Utils Messenger Creation Function!\n");
	}
	else
	{
		//Debug Function Location Success
		if(this -> verbose)
		{
			std::cout << "Successfully Located & Loaded VKDT Vulkan Create Debug Utils Messenger Function!\n";
		}
	}

	//Create Debug Utils Messenger
	const VkResult vkdtVKCreateDebugUtilsMessengerResult = createVKDebugUtilsMessengerEXT
	(
		this -> vkdtVKInstance,
		&debugMessengerCreateInfo,
		this -> pAllocator,
		&this -> vkdtVKDebugMessenger
	);

	if(vkdtVKCreateDebugUtilsMessengerResult == VK_SUCCESS)
	{
		//Debug Creation Success
		if(this -> verbose)
		{
			std::cout << "Successfully Created VKDT Debug Utils Messenger, Simulating Function...\n";

			//Vulkan Callback Data Information
			const VkDebugUtilsMessengerCallbackDataEXT callbackData =
			{
				//Struct Type
				.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT,

				//Message Information
				.pMessageIdName = "VKDT Callback",
				.pMessage = "VKDT Simulation of Implemented Callback Function, Caused by Verbose Option in Settings!",
				.messageIdNumber = -1,
			};

			//Call Function
			vkdtVKDebugCallback
			(
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT,
				VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,
				&callbackData,
				VK_NULL_HANDLE
			);
		}

		else if(this -> debug)
		{
			std::cout << "Successfully Created VKDT Debug Utils Messenger!\n";
		}
	}
	else
	{
		throw std::runtime_error
		(
			"Failed to Create VKDT Vulkan Debug Utils Messenger! Error: " +
			std::to_string(vkdtVKCreateDebugUtilsMessengerResult) + "!\n"
		);
	}
}

void vkdt::instance::instance::destroyVKDTDebugMessenger(void)
{
	//Destroy Debug Utils Messenger
	if(this -> debug || this -> verbose)
	{
		//Locate & Load Function to Destroy Vulkan Debug Utils
		const PFN_vkDestroyDebugUtilsMessengerEXT destroyVKDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>
		(
			vkGetInstanceProcAddr
			(
				this -> vkdtVKInstance,
				"vkDestroyDebugUtilsMessengerEXT"
			)
		);

		//Check if Function is Created Successfully
		if(!destroyVKDebugUtilsMessengerEXT)
		{
			throw std::runtime_error("Failed to Locate & Load VKDT Vulkan Debug Utils Messenger Creation Function!\n");
		}
		else
		{
			//Debug Function Location Success
			if(this -> verbose)
			{
				std::cout << "Successfully Located & Loaded VKDT Vulkan Destroy Debug Utils Messenger Function!\n";
			}
		}

		//Call Function to Vulkan Destroy Debug Utils Messenger
		destroyVKDebugUtilsMessengerEXT(this -> vkdtVKInstance, this -> vkdtVKDebugMessenger, this -> pAllocator);
	}
}

const VkInstance& vkdt::instance::instance::refVKInstance(void) const noexcept
{
	return this -> vkdtVKInstance;
}

const VkDebugUtilsMessengerEXT& vkdt::instance::instance::refVKDebugMessenger(void) const noexcept
{
	return this -> vkdtVKDebugMessenger;
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
			"Failed to Find Number of VKDT Vulkan Instance Extension Properties! Error: " +
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
			"Failed to Find VKDT Vulkan Instance Extension Properties! Error: " +
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
			"Failed to Find VKDT Vulkan Instance Layer Properties! Error: " +
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

inline void vkdt::instance::instance::fillDebugUtilsCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerCreateInfo)const noexcept
{
	debugMessengerCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,

		//Message Severity to Debug
		.messageSeverity =																			\
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |											\
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |											\
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,


		//Message Types to Debug
		.messageType =																				\
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |											\
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT  |											\
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,

		//Debug Callback Function
		.pfnUserCallback = vkdtVKDebugCallback,
	};
}

vkdt::instance::instance::~instance() noexcept(false)
{
	//Destroy VKDT Vulkan Instance
	vkDestroyInstance(this -> vkdtVKInstance, this -> pAllocator);

	if(this -> verbose)
	{
		//Debug Deletion Success
		std::cout << "Successfully Destroyed VKDT Vulkan Instance!\n";
	}

#ifdef __APPLE__

	//Unset MoltenVK Required Environment Variable
	if(this -> macOSEnvVariables.VK_ICD_FILENAMES && unsetenv("VK_ICD_FILENAMES") == 0)
	{
		//Debug Success
		if(this -> verbose)
		{
			std::cout << "Successfully Unset: \"" << "VK_ICD_FILENAMES" << "\"!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Unset: \"VK_ICD_FILENAMES\" Environment Variable!\n");
	}

	//Unset Vulkan Layer(s) Required Environment Variables
	if(this -> macOSEnvVariables.VK_LAYER_PATH && unsetenv("VK_LAYER_PATH") == 0)
	{
		//Debug Success
		if(this -> verbose)
		{
			std::cout << "Successfully Unset: \"" << "VK_LAYER_PATH" << "\"!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Unset: \"VK_LAYER_PATH\" Environment Variable!\n");
	}

#endif
}