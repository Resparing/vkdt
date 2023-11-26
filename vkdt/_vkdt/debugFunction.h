//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace vkdt::debug
{
	//Message Severities Enum
	enum class messageSeverity : uint32_t
	{
		VERBOSE 				= 0x00001,
		INFO 					= 0x00010,
		WARNING 				= 0x00100,
		ERROR 					= 0x01000,
	};

	//Message Types Enum
	enum class messageType : uint32_t
	{
		VERBOSE 				= 0x00000,
		GENERAL 				= 0x00001,
		VALIDATION 				= 0x00002,
		PERFORMANCE 			= 0x00004,
		DEVICE_ADDRESS_BINDING 	= 0x00008,
	};

	//Queue Label & Command Buffer Struct
	struct label
	{
		//Name of Queue Label
		std::string labelName;

		//Array of Colors
		std::array<float, 4> color;
	};

	//Object Struct
	struct object
	{
		//Name of Object
		std::string objectName;

		//Type of Object
		VkObjectType objectType;

		//Handle of Object
		uintptr_t objectHandle;
	};

	//Message Data Struct
	struct messageData
	{
		//Message
		std::string message;

		//Message ID & Message ID Name
		int32_t messageID;
		std::string messageIDName;

		//Vector of Labels, Command Buffers & Objects
		std::vector<vkdt::debug::label> queueLabels;
		std::vector<vkdt::debug::label> commandBuffers;
		std::vector<vkdt::debug::object> objects;
	};

	/**
	 * @brief VKDT Callback Function Parameters
	 */
	typedef void(*vkdtCallback)
	(
		const vkdt::debug::messageSeverity,  //VKDT Message Severity	
		const vkdt::debug::messageType,  //VKDT Message Type
		const vkdt::debug::messageData  //VKDT Message Data
	);

	/**
	 * @brief Callback Function for VKDT Debug Messenger
	 *
	 * @attention Only Intended for Vulkan API & VKDT Callbacks
	 */
	static vkdt::debug::vkdtCallback vkdtCallbackFunc{};
}