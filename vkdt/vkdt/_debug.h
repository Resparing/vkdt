//Header Guard
#pragma once

//Include Headers
#include <vkdt/_vkdtConfig.h>

namespace vkdt::debug
{
	/**
	 * @brief VKDT Callback Function Parameters
	 */
	typedef void(*vkdtCallback)
	(
		/**
		 * @brief Vulkan Message Severity
		 */
		const VkDebugUtilsMessageSeverityFlagBitsEXT,

		/**
		 * @brief Vulkan Message Type
		 */
		const VkDebugUtilsMessageTypeFlagsEXT,

		/**
		 * @brief Vulkan Message Data
		 */
		const VkDebugUtilsMessengerCallbackDataEXT*
	);

	/**
	 * @brief Callback Function for VKDT Debug Messenger
	 *
	 * @attention Only Intended for Vulkan API and VKDT Callbacks
	 */
	static vkdt::debug::vkdtCallback vkdtCallbackFunc{};
}