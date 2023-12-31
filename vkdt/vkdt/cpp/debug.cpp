//Include Header File
#include <vkdt/debug.h>

//Include Headers
#include <_vkdt/pObjects.h>

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
		throw std::runtime_error("Vulkan Debug Callback Function Contains Invalid Information!\n");
	}

	//Convert Vulkan Message Severity & Type into VKDT Message Severity & Type
	const vkdt::debug::messageSeverity vkdtMessageSeverity = static_cast<vkdt::debug::messageSeverity>(messageSeverity);
	vkdt::debug::messageType vkdtMessageType = static_cast<vkdt::debug::messageType>(messageType);

	//Change VKDT Message Type to Verbose if Set to Max Enum
	if(messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_FLAG_BITS_MAX_ENUM_EXT)
	{
		vkdtMessageType = vkdt::debug::messageType::VERBOSE;
	}

	//Vector of Queue Labels, Command Buffers & Objects
	std::vector<const vkdt::debug::label> queueLabels;
	std::vector<const vkdt::debug::label> commandBuffers;
	std::vector<const vkdt::debug::object> objects;

	//Set Queue Labels
	for(size_t i{}; i < pCallbackData -> queueLabelCount; ++i)
	{
		const struct vkdt::debug::label queueLabel =
		{
			//Set Label Name
			.labelName = pCallbackData -> pQueueLabels[i].pLabelName,

			//Set Colors
			.color =																				\
			{																						\
				pCallbackData -> pQueueLabels[i].color[0],											\
				pCallbackData -> pQueueLabels[i].color[1],											\
				pCallbackData -> pQueueLabels[i].color[2],											\
				pCallbackData -> pQueueLabels[i].color[3],											\
			},
		};

		//Add to Queue Labels Vector
		queueLabels.push_back(queueLabel);
	}

	//Set Command Buffers
	for(size_t i{}; i < pCallbackData -> cmdBufLabelCount; ++i)
	{
		const struct vkdt::debug::label commandBuffer =
		{
			//Set Label Name
			.labelName = pCallbackData -> pCmdBufLabels[i].pLabelName,

			//Set Colors
			.color =																				\
			{																						\
				pCallbackData -> pCmdBufLabels[i].color[0],											\
				pCallbackData -> pCmdBufLabels[i].color[1],											\
				pCallbackData -> pCmdBufLabels[i].color[2],											\
				pCallbackData -> pCmdBufLabels[i].color[3],											\
			},
		};

		//Add to Command Buffers Vector
		commandBuffers.push_back(commandBuffer);
	}

	//Set Objects
	for(size_t i{}; i < pCallbackData -> objectCount; ++i)
	{
		const struct vkdt::debug::object object =
		{
			//Set Object Name
//			.objectName = pCallbackData -> pObjects[i].pObjectName,

			//Set Object Type & Handle
			.objectType = pCallbackData -> pObjects[i].objectType,
			.objectHandle = pCallbackData -> pObjects[i].objectHandle,
		};

		//Add to Objects Vector
		objects.push_back(object);
	}

	//Set VKDT Message Data
	const struct vkdt::debug::messageData messageData =
	{
		//Set Message Information
		.messageIDName = pCallbackData -> pMessageIdName,
		.messageID = pCallbackData -> messageIdNumber,
		.message = pCallbackData -> pMessage,

		//Set Additional Vector Data
		.queueLabels = queueLabels,
		.commandBuffers = commandBuffers,
		.objects = objects,
	};

	//Call VKDT Debug Function
	vkdt::debug::vkdtCallbackFunc(vkdtMessageSeverity, vkdtMessageType, messageData);

	//Mandatory Return Statement
	return VK_FALSE;
}

vkdt::debug::messenger::messenger
(
	vkdt::debug::vkdtCallback callbackFunction,
	const bool debug,
	const bool verbose
) noexcept : debug(debug), verbose(verbose)
{
	//Stop if not Debugging
	if(this -> debug == false && this -> verbose == false)
	{
		return;
	}

	//Set Vulkan Debug Messenger & Class Pointers
	_vkdt::pObjects::pVKDebugMessenger = &this -> vkdtVKDebugMessenger;
	_vkdt::pObjects::pVKDTDebugMessenger = this;

	//Set Callback Function
	vkdt::debug::vkdtCallbackFunc = callbackFunction;

	//Fill Vulkan Debug Utils Creation Information Struct
	this -> fillDebugUtilsCreateInfo(this -> debugMessengerCreateInfo);

	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT Debug Messenger!\n";
	}
}

vkdt::debug::messenger::~messenger() noexcept(false)
{
	//Destroy Debug Utils Messenger
	if(this -> debug || this -> verbose)
	{
		//Locate & Load Function to Destroy Vulkan Debug Utils
		const PFN_vkDestroyDebugUtilsMessengerEXT destroyVKDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>
		(
			vkGetInstanceProcAddr
			(
				*_vkdt::pObjects::pVKInstance,
				"vkDestroyDebugUtilsMessengerEXT"
			)
		);

		//Check if Function is Created Successfully
		if(!destroyVKDebugUtilsMessengerEXT)
		{
			throw std::runtime_error("Failed to Locate & Load Vulkan Debug Utils Messenger Creation Function!\n");
		}
		else
		{
			//Debug Function Location Success
			if(this -> verbose)
			{
				std::cout << "Successfully Located & Loaded Vulkan Destroy Debug Utils Messenger Function!\n";
			}
		}

		//Call Function to Vulkan Destroy Debug Utils Messenger
		destroyVKDebugUtilsMessengerEXT(*_vkdt::pObjects::pVKInstance, this -> vkdtVKDebugMessenger, this -> pAllocator);
	}
}

void vkdt::debug::messenger::createVKDTDebugMessenger(VkAllocationCallbacks* allocator)
{
	if(this -> debug == false && this -> verbose == false)
	{
		return;
	}

	//Set Vulkan Allocator
	this -> pAllocator = allocator;

	//Locate & Load Function to Create Vulkan Debug Utils Messenger
	this -> createVKDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>
	(
		vkGetInstanceProcAddr
		(
			*_vkdt::pObjects::pVKInstance,
			"vkCreateDebugUtilsMessengerEXT"
		)
	);

	//Check if Function Created Successfully
	if(!createVKDebugUtilsMessengerEXT)
	{
		throw std::runtime_error("Failed to Locate & Load Vulkan Debug Utils Messenger Creation Function!\n");
	}
	else
	{
		//Debug Function Location Success
		if(this -> verbose)
		{
			std::cout << "Successfully Located & Loaded Vulkan Create Debug Utils Messenger Function!\n";
		}
	}

	//Create Debug Utils Messenger
	const VkResult vkdtVKCreateDebugUtilsMessengerResult = createVKDebugUtilsMessengerEXT
	(
		*_vkdt::pObjects::pVKInstance,
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
			"Failed to Create VKDT Debug Utils Messenger! Error: " +
			std::to_string(vkdtVKCreateDebugUtilsMessengerResult) + "!\n"
		);
	}
}

void vkdt::debug::messenger::fillDebugUtilsCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerCreateInfo) noexcept
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