//Header Guard
#pragma once

//Include Headers
#include <_vkdt/instanceStruct.h>
#include <_vkdt/vkdtConfig.h>

namespace vkdt::instance
{
	class instance
	{
	public:

		/**
		 * @brief Initialize VKDT Instance & Parse Application Information
		 *
		 * @param applicationInfo The Application Information of Program
		 * @param debug Whether to Allow Debugging in Messages and Setup Debug Callback
		 * @param verbose Allow General & Verbose Debugging Methods in Messages and Setup Debug Callback
		 */
		instance
		(
			const vkdt::instance::applicationData& applicationInfo,
			const bool debug = false,
			const bool verbose = false
		) noexcept;

		virtual ~instance();

		/**
		 * @brief Set up the Creation of VKDT Instance
		 *
		 * @param vkdtExtensions C-String Vector of Requested Vulkan Extensions
		 * @param vkdtLayers C-String Vector of Requested Vulkan Layers
		 */
		void setupVKDTInstance
		(
			const std::vector<const char*>& vkdtRequestedExtensions = {},
			const std::vector<const char*>& vkdtRequestedLayers = {}
		);

		/**
		 * @brief Create VKDT Instance
		 *
		 * @param allocator Vulkan Memory Allocator
		 */
		void createVKDTInstance(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);

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

	protected:

		//Options for Debugging
		bool debug{};
		bool verbose{};

		//Vulkan Instance
		VkInstance vkdtVKInstance;  //Vulkan Instance
	};
}