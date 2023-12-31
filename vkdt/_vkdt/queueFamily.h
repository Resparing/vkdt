//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace _vkdt::queueFamily
{
	struct Indices
	{
		std::optional<uint32_t> vkdtVKGraphicsFamily{};
		std::optional<uint32_t> vkdtVKPresentFamily{};

		/**
		 * @brief Check if VKDT Struct Contains a Value
		 *
		 * @return true if Items in Struct Contain Value, false if not
		 */
		bool isComplete(void) const noexcept;
	};

	/**
	 * @brief Get Indexes of Vulkan Queue Family Indexes
	 *
	 * @param vkdtVKPhysicalDevice Reference to Vulkan Physical Device
	 * @param debug Whether to Allow Debugging in Messages
	 * @param verbose Allow General & Verbose Debugging Methods in Messages
	 *
	 * @return Struct of Indexes that Contain Information of Vulkan Queue Family Indexes
	 */
	struct _vkdt::queueFamily::Indices findQueueFamilyIndices
	(
		const VkPhysicalDevice& vkdtVKPhysicalDevice,
		const bool debug = false,
		const bool verbose = false
	);
}