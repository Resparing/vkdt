//Header Guard
#pragma once

//Include Headers
#include <vkdt/_vkdtConfig.h>

namespace vkdt::instance
{
	/**
	 * @brief VKDT Instance Application Data
	 */
	struct applicationData
	{
		//Name of VKDT Application
		const char* name;

		//Struct with Version Information
		struct appVersion
		{
			std::uint32_t variant;
			std::uint32_t major;
			std::uint32_t minor;
			std::uint32_t patch;
		}; appVersion version;
	};

	//Vulkan Enviornment Variables
	struct envVariables
	{
		//MoltenVK JSON Information Path
		const char* VK_ICD_FILENAMES;

		//Vulkan Layer JSON Information Directory
		const char* VK_LAYER_PATH;
	};
}