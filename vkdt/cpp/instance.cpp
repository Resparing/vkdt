//Include Header File
#include <vkdt/instance.h>

//Include Headers

/**
 * @brief Vulkan Needed Implementation of VKDT Callback
 *
 * @param messageSeverity Severity of Vulkan Message to Debug
 * @param messageType Type of Vulkan Message to Debug
 * @param pCallbackData Information on Vulkan Message to Debug
 * @param pUserData Optional Data - Contains VKDT Callback Function Abstraction
 *
 * @return VK_FALSE, Mandatory Return Statement
 */
static VkBool32 VKAPI_ATTR VKAPI_CALL vkdtVKDebugCallback
(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData
)
{
	//Check if User Data Contains Anything
	if(pUserData != NULL && pUserData != nullptr && pUserData != VK_NULL_HANDLE)
	{
		throw std::runtime_error("User Data Contains Invalid Information!\n");
	}

	//Call VKDT Debug Function
	vkdt::debug::vkdtCallbackFunc(messageSeverity, messageType, pCallbackData);

	//Mandatory Return Statement
	return VK_FALSE;
}

vkdt::instance::instance::instance
(
	const vkdt::instance::applicationInfo& applicationInfo,
	const bool debug,
	const bool verbose,
	const std::vector<const char*> vkdtRequestedExtensions,
	const std::vector<const char*> vkdtRequestedLayers
) : appData(applicationInfo), vkdtExtensions(vkdtRequestedExtensions), vkdtLayers(vkdtRequestedLayers), debug(debug), verbose(verbose)
{
	//Debug VKDT Instance Information
	if(verbose)
	{
		//Debug Application Information
		std::cout																			\
		<< "Successfully Received Application Information With"							 \
		<< " Name: \"" << this -> appData.name											  \
		<< "\" Version: Patch " << this -> appData.version.patch							\
		<< ", Major " << this -> appData.version.major									  \
		<< ", Minor " << this -> appData.version.minor									  \
		<< ". Variant: " << this -> appData.version.variant << "!\n";
	}

	else if(this -> debug)
	{
		std::cout																			\
		<< "Successfully Received Application Information With"							 \
		" Name: \"" << this -> appData.name												 \
		<< "\", Version: " << this -> appData.version.patch								 \
		<< "." << this -> appData.version.major											 \
		<< "." << this -> appData.version.minor											 \
		<< "." << this -> appData.version.variant << "!\n";
	}

	//Add Required GLFW Extensions
	std::uint32_t vkdtGLFWExtensionCount{};  //Number of Extensions
	const char** vkdtGLFWExtensions{};  //Names of Extensions
	vkdtGLFWExtensions = glfwGetRequiredInstanceExtensions(&vkdtGLFWExtensionCount);  //Get GLFW Required Extensions

	//Check if Vulkan Extensions are Requested
	if(vkdtGLFWExtensions == NULL)
	{
		throw std::runtime_error("Required GLFW Vulkan Extensions not Found!\n");
	}

	//Debug GLFW Extensions
	if(this -> verbose)
	{
		std::cout << "Adding Required GLFW Extensions (" << vkdtGLFWExtensionCount << "):\n";
	}

	else if(this -> debug)
	{
		std::cout << "Adding Required Extensions: " << vkdtGLFWExtensionCount << "!\n";
	}

	//Add GLFW Extensions to VKDT Extensions
	for(std::uint32_t i{}; i < vkdtGLFWExtensionCount; ++i)
	{
		vkdtExtensions.push_back(vkdtGLFWExtensions[i]);

		//Debug Information
		if(this -> verbose)
		{
			std::cout << "\t\"" << vkdtGLFWExtensions[i] << "\"\n";
		}
	}

	//Add VKDT Vulkan Debugging Extensions & Layers
	if(this -> debug || this -> verbose)
	{
		this -> vkdtLayers.push_back("VK_LAYER_KHRONOS_validation");
		this -> vkdtExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		if(this -> verbose)
		{
			std::cout																		\
			<< "Added Required Debugging Software: \"" << "VK_LAYER_KHRONOS_validation"	 \
			<< "\" and: \"" << VK_EXT_DEBUG_UTILS_EXTENSION_NAME << "\"!\n";
		}
	}

#ifdef __APPLE__
	//Add Required MacOS Extension & Flags
	this -> vkdtExtensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	this -> vkdtVKFlags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

	//Debug Required Added Extension
	if(this -> debug || this -> verbose)
	{
		std::cout << "Added Required MacOS Vulkan Extension: \"" << VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME << "\"!\n";
	}
#endif

	//If Verbose Debugging
	if(this -> verbose)
	{
		//Debug Requested Extensions - At Least Contains VK_KHR_surface Extension
		std::cout << "Added Requested VKDT Vulkan Extensions (" << this -> vkdtExtensions.size() << "):\n";

		for(const char*& vkdtExtension : this -> vkdtExtensions)
		{
			std::cout << "\t\"" << vkdtExtension << "\"\n";
		}

		//No Vulkan Layers may Requested
		if(this -> vkdtLayers.size() > 0)
		{
			//Debug Requested Layers
			std::cout << "Added Requested VKDT Vulkan Layers (" << this -> vkdtLayers.size() << "):\n";

			for(const char*& vkdtLayer : this -> vkdtLayers)
			{
				std::cout << "\t\"" << vkdtLayer << "\"\n";
			}
		}
	}
	else if(this -> debug)
	{
		//Debug Number of Requested Vulkan Extensions & Vulkan Layers
		std::cout << "Added: " << this -> vkdtExtensions.size() << " VKDT Vulkan Extensions!\n";
		std::cout << "Added: " << this -> vkdtLayers.size() << " VKDT Vulkan Layers!\n";
	}
}

void vkdt::instance::instance::createVKDTInstance(const VkAllocationCallbacks* allocator)
{
	//Set Allocator
	this -> pAllocator = const_cast<VkAllocationCallbacks*>(allocator);

	//Vulkan Application Information Struct
	const VkApplicationInfo instanceAppInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,

		//Vulkan API Version
		.apiVersion = VK_HEADER_VERSION_COMPLETE,

		//Engine Information
		.pEngineName = "VKDT Engine",
		.engineVersion = VK_HEADER_VERSION_COMPLETE,

		//Application Information
		.pApplicationName = this -> appData.name,
		.applicationVersion = VK_MAKE_API_VERSION											\
		(																					\
			this -> appData.version.variant,												\
			this -> appData.version.major,												  \
			this -> appData.version.minor,												  \
			this -> appData.version.patch													\
		),
	};

	//Vulkan Create Instance Information Struct
	VkInstanceCreateInfo instanceCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,

		//Pointer to Vulkan Application Information
		.pApplicationInfo = &instanceAppInfo,

		//Vulkan Instance Extensions
		.enabledExtensionCount = static_cast<uint32_t>(this -> vkdtExtensions.size()),
		.ppEnabledExtensionNames = this -> vkdtExtensions.data(),

		//Vulkan Instance Layers
		.enabledLayerCount = static_cast<uint32_t>(this -> vkdtLayers.size()),
		.ppEnabledLayerNames = this -> vkdtLayers.data(),

		//Vulkan Flags
		.flags  = vkdtVKFlags,
	};

	//Create Vulkan Instance
	if(vkCreateInstance(&instanceCreateInfo, this -> pAllocator, &this -> vkdtVKInstance) == VK_SUCCESS)
	{
		if(this -> debug || this -> verbose)
		{
			std::cout << "Successfully Created VKDT Vulkan Instance!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Vulkan Instance!\n");
	}
}

void vkdt::instance::instance::makeVKDTDebugMessenger(vkdt::debug::vkdtCallback callbackFunc)
{
	//Stop if not Debugging
	if(this -> debug == false || this -> verbose == false)
	{
		return;
	}

	//Set Callback Function
	vkdt::debug::vkdtCallbackFunc = callbackFunc;

	//VKDT Vulkan Debug Utils Messenger Creation Information Struct
	VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo;

	//Fill Struct
	this -> fillDebugUtilsCreateInfo(debugMessengerCreateInfo);

	//Find VKDT Vulkan Debug Utils Messenger Creation Function
	const PFN_vkCreateDebugUtilsMessengerEXT createDebugUtilsMessenger =					\
	(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(this -> vkdtVKInstance, "vkCreateDebugUtilsMessengerEXT");

	//Check if Function Found Successfully
	if(createDebugUtilsMessenger == nullptr || createDebugUtilsMessenger == NULL || createDebugUtilsMessenger == VK_NULL_HANDLE)
	{
		throw std::runtime_error("Failed to Find VKDT Create Debug Utils Messenger Function!\n");
	}

	//Create Vulkan Debug Utils Messenger
	if(createDebugUtilsMessenger
	(
		this -> vkdtVKInstance,
		&debugMessengerCreateInfo,
		this -> pAllocator,
		&this -> vkdtVKDebugMessenger
	) == VK_SUCCESS)
	{
		if(this -> verbose)
		{
			//Error Struct
			const VkDebugUtilsMessengerCallbackDataEXT callbackData =
			{
				//Struct Type
				.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT,

				//Message Information
				.pMessageIdName = "VKDT Callback Function Test",
				.messageIdNumber = -1,
				.pMessage = "Test Callback Data Caused by VKDT Verbose Output!"
			};

			//Simulate Error
			vkdtVKDebugCallback
			(
				//Set Message Severity to Verbose
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT,

				//Set Message Type to General
				VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,

				//Give Debug Callback Pointer
				&callbackData,

				//Set User Data
				VK_NULL_HANDLE
			);
		}
		else if(this -> debug)
		{
			std::cout << "Successfully Created VKDT Vulkan Debug Utils Messenger!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create VKDT Vulkan Debug Utils Messenger!\n");
	}
}

const VkInstance& vkdt::instance::instance::refVKInstance(void) noexcept
{
	return this -> vkdtVKInstance;
}

bool vkdt::instance::instance::requestedExtensionsSupported(void) const
{
	//Check Vulkan Extensions
	std::uint32_t vkdtVKAvailableExtensionCount{};

	if(vkEnumerateInstanceExtensionProperties(nullptr, &vkdtVKAvailableExtensionCount, nullptr) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find Number of VKDT Vulkan Instance Extension Properties!\n");
	}

	std::vector<VkExtensionProperties> vkdtVKAvailableExtensions(vkdtVKAvailableExtensionCount);

	if(vkEnumerateInstanceExtensionProperties(nullptr, &vkdtVKAvailableExtensionCount, vkdtVKAvailableExtensions.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find VKDT Vulkan Instance Extension Properties!\n");
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

	if(vkEnumerateInstanceLayerProperties(&vkdtVKAvailableLayerCount, nullptr) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find Number of VKDT Vulkan Instance Layer Properties!\n");
	}

	std::vector<VkLayerProperties> vkdtVKAvailableLayers(vkdtVKAvailableLayerCount);

	if(vkEnumerateInstanceLayerProperties(&vkdtVKAvailableLayerCount, vkdtVKAvailableLayers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to Find VKDT Vulkan Instance Layer Properties!\n");
	}

	//Debug Number of Vulkan Layers
	if(this -> verbose)
	{
		std::cout << "Available VKDT Vulkan Layers (" << vkdtVKAvailableLayerCount << "):\n";

		for(const VkLayerProperties& vkdtVKAvailableLayer : vkdtVKAvailableLayers)
		{
			std::cout																		\
			<< "\t\"" << vkdtVKAvailableLayer.layerName									 \
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

inline void vkdt::instance::instance::fillDebugUtilsCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerCreateInfo) noexcept
{
	debugMessengerCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,

		//Message Severity to Debug
		.messageSeverity =																  \
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |									\
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |									\
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,


		//Message Types to Debug
		.messageType =																	  \
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |									\
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT  |									\
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,

		//Debug Callback Function
		.pfnUserCallback = vkdtVKDebugCallback,
	};
}

vkdt::instance::instance::~instance() noexcept(false)
{
	if(this -> debug || this -> verbose)
	{
		//Find VKDT Vulkan Debug Utils Messenger Destruction Function
		const PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugUtilsMessenger =			  \
		(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(this -> vkdtVKInstance, "vkDestroyDebugUtilsMessengerEXT");

		//Check if Function Found Successfully
		if(destroyDebugUtilsMessenger == nullptr || destroyDebugUtilsMessenger == NULL || destroyDebugUtilsMessenger == VK_NULL_HANDLE)
		{
			throw std::runtime_error("Failed to Find VKDT Create Debug Utils Messenger Function!\n");
		}

		//Call Function
		destroyDebugUtilsMessenger(this -> vkdtVKInstance, this -> vkdtVKDebugMessenger, this -> pAllocator);

		if(this -> verbose)
		{
			//Debug VKDT Vulkan Debug Utils Messenger Destruction Success
			std::cout << "Successfully Destroyed VKDT Debug Messenger!\n";
		}
	}

	//Destroy VKDT Vulkan Instance
	vkDestroyInstance(this -> vkdtVKInstance, this -> pAllocator);

	if(this -> verbose)
	{
		//Debug Deletion Success
		std::cout << "Successfully Destroyed VKDT Vulkan Instance!\n";
	}
}