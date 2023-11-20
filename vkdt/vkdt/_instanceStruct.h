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
		std::string name;

		/**
		 * @brief Struct with Version Information
		 */
		struct appVersion
		{
			std::uint32_t variant;
			std::uint32_t major;
			std::uint32_t minor;
			std::uint32_t patch;
		}; appVersion version;
	};

	/**
	 * @brief Vulkan Enviornment Variables
	 */
	struct envVariables
	{
		//MoltenVK JSON Information Path
		const std::string VK_ICD_FILENAMES;

		//Vulkan Layer JSON Information Directory
		const std::string VK_LAYER_PATH;
	};
}