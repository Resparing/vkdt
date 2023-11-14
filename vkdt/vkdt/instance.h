//Header Guard
#pragma once

//Include Headers
#include <vkdt/_debug.h>
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

	//Instance Class
	class instance
	{
	public:

		/**
		 * @brief Initialize VKDT Vulkan Instance & Set up Requested Layers and Extensions
		 *
		 * @param applicationInfo The Application Information of Program
		 * @param callbackFunc Function for Debugging Errors
		 * @param vkdtExtensions C-String Vector of Requested Vulkan Extensions
		 * @param vkdtLayers C-String Vector of Requested Vulkan Layers
		 * @param debug Whether to Allow Debugging in Messages and Setup Debug Callback
		 * @param verbose Allow General & Verbose Debugging Methods in Messages and Setup Debug Callback
		 */
		instance
		(
			const vkdt::instance::applicationData& applicationInfo,
			const std::vector<const char*> vkdtRequestedExtensions = {},
			const std::vector<const char*> vkdtRequestedLayers = {},
			const bool debug = false,
			const bool verbose = false
		);

		virtual ~instance() noexcept(false);

		/**
		 * @brief Create VKDT Instance
		 *
		 * @attention When Debugging,
		 *
		 * @param callbackFunc Function used by VKDT Debug Messenger Debugger
		 * @param allocator Vulkan Memory Allocator
		 */
		void createVKDTInstance(vkdt::debug::vkdtCallback callbackFunc = VK_NULL_HANDLE, VkAllocationCallbacks* allocator = VK_NULL_HANDLE);

		/**
		 * @brief Initialize VKDT Debug Messenger
		 *
		 * @param callbackFunc Function used When Printing
		 */
		void makeVKDTDebugMessenger();

		/**
         * @brief Get a Reference to VKDT Vulkan Instance
		 *
		 * @attention Use for Extending VKDT Instance Class and for Internal Use!
		 *
		 * @return Reference to Vulkan Instance
         */
		const VkInstance& refVKInstance(void) const noexcept;

		/**
         * @brief Get a Reference to VKDT Vulkan Debug Messenger
		 *
		 * @attention Use for Extending VKDT Instance Class and for Internal Use!
		 *
		 * @return Reference to Vulkan Debug Messenger
         */
		const VkDebugUtilsMessengerEXT& refVKDebugMessenger(void) const noexcept;

	private:

		//Application Data
		vkdt::instance::applicationData appData{};

		//Vector of VKDT Layers & Extensions
		std::vector<const char*> vkdtExtensions{};
		std::vector<const char*> vkdtLayers{};

		//Vulkan Instance Creation Information Flags
		std::uint32_t vkdtVKInstanceCreateInfoFlags{};

		//Vulkan Allocator
		VkAllocationCallbacks* pAllocator;

		/**
		 * @brief Check if Vulkan Extensions are Supported
		 *
		 * @return true, if all Tests Pass, false if not
		 */
		bool requestedExtensionsSupported(void) const;

		/**
		 * @brief Check if Vulkan Layers are Supported
		 *
		 * @return true, if all Tests Pass, false if not
		 */
		bool requestedLayersSupported(void) const;

		/**
		 * @brief Fill VKDT Create Info Struct
		 *
		 * @param debugMessengerCreateInfo Reference to Debug Utils Creation Information Struct
		 */
		inline void fillDebugUtilsCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerCreateInfo) const noexcept;

	protected:

		//Options for Debugging
		bool debug{};
		bool verbose{};

		/* Vulkan Parameters */
		VkInstance vkdtVKInstance;  //Vulkan Instance
		VkDebugUtilsMessengerEXT vkdtVKDebugMessenger;  //Vulkan Debug Utils Messenger
	};
}