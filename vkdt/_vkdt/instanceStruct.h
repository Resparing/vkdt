//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

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
}