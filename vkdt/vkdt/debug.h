//Header Guard
#pragma once

//Include Headers
#include <vkdt/_vkdtConfig.h>
#include <vkdt/_debugFunction.h>

namespace vkdt::debug
{
	class messenger
	{
	public:

		/**
		 * @brief Initialize & Setup VKDT Debug Messenger
		 *
		 * @param callbackFunc Function used by VKDT Debug Messenger Debugger
		 * @param debug Whether to Allow Debugging in Messages
	 	 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		messenger(vkdt::debug::vkdtCallback callbackFunc = VK_NULL_HANDLE, const bool debug = false, const bool verbose = false) noexcept;

		virtual ~messenger() noexcept(false);

		/**
		 * @brief Create VKDT Debug Messenger
		 *
		 * @param allocator Vulkan Memory Allocator
		 */
		void createVKDTDebugMessenger(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);

		/**
		 * @brief Fill VKDT Create Info Struct
		 *
		 * @attention Use for Extending VKDT Messenger Class and for Internal Use!
		 *
		 * @param debugMessengerCreateInfo Reference to Debug Utils Creation Information Struct
		 */
		static void fillDebugUtilsCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerCreateInfo) noexcept;

	private:

		//Vulkan Allocator
		VkAllocationCallbacks* pAllocator;

		//Create Vulkan Debug Messenger Function
		PFN_vkCreateDebugUtilsMessengerEXT createVKDebugUtilsMessengerEXT;

		//Debug Messenger Creation Information Struct
		VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo = {};

	protected:

		//Vulkan Debug Utils Messenger
		VkDebugUtilsMessengerEXT vkdtVKDebugMessenger;

		//Debugging Variables
		bool debug{};
		bool verbose{};

	};
}