//Header Guard
#pragma once

//Include Headers
#include <vkdt/_vkdtConfig.h>

namespace vkdt::debug
{
	//Callback Function Parameters
	typedef void(*vkdtCallback)
	(
		const VkDebugUtilsMessageSeverityFlagBitsEXT,
		const VkDebugUtilsMessageTypeFlagsEXT,
		const VkDebugUtilsMessengerCallbackDataEXT*
	);

	/**
	 * @brief Callback Function for VKDT Debug Messenger
	 *
	 * @attention Only Intended for Vulkan API and VKDT Callbacks
	 */
	static vkdt::debug::vkdtCallback vkdtCallbackFunc;
}

namespace vkdt::instance
{
	//Application Data
	struct applicationInfo
	{
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
		 * @brief Initialize VKDT Vulkan Instance and Set's up Requested Layers and Extensions
		 *
		 * @param appInfo The Application Information of Program
		 * @param debug Whether to Allow Debugging in Messages and Setup Debug Callback
		 * @param verbose Allow Verbose Debugging Methods in Messages and Setup Debug Callback
		 * @param callbackFunc Function for Debugging Errors
		 * @param vkdtExtensions C-String Vector of Requested Vulkan Extensions
		 * @param vkdtLayers C-String Vector of Requested Vulkan Layers
		 */
		instance
		(
			const vkdt::instance::applicationInfo& applicationInfo,
			const bool debug = false,
			const bool verbose = false,
			const std::vector<const char*> vkdtRequestedExtensions = {},
			const std::vector<const char*> vkdtRequestedLayers = {}
		);

		virtual ~instance() noexcept(false);

		/**
		 * @brief Create VKDT Instance
		 */
		void createVKDTInstance(const VkAllocationCallbacks* allocator = VK_NULL_HANDLE);

		/**
		 * @brief Initialize VKDT Debug Messenger
		 *
		 * @param callbackFunc Function used When Printing
		 */
		void makeVKDTDebugMessenger(vkdt::debug::vkdtCallback callbackFunc);

		/**
		 * @brief Get a Pointer to Vulkan Instance
		 *
		 * @attention Only use if Extending Features or Filling Missing Implementations
		 *
		 * @return Pointer to Vulkan Instance
		 */
		VkInstance& refVKInstance(void) noexcept;

	private:

		//Application Data
		vkdt::instance::applicationInfo appData{};

		//Vector of VKDT Layers & Extensions
		std::vector<const char*> vkdtExtensions{};
		std::vector<const char*> vkdtLayers{};

		//Vulkan Flags
		std::uint32_t vkdtVKFlags{};

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
		inline void fillDebugUtilsCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerCreateInfo) noexcept;

	protected:

		//Options for Debugging
		bool debug{};
		bool verbose{};

		/* Vulkan Parameters */
		VkInstance vkdtVKInstance;  //Vulkan Instance
		VkDebugUtilsMessengerEXT vkdtVKDebugMessenger;  //Vulkan Debug Utils Messenger
	};
}