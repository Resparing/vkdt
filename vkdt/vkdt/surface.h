//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace vkdt::surface
{
	class surface
	{
	public:

		/**
		 * @brief Initialize VKDT Surface
		 *
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */

		surface(const bool debug = false, const bool verbose = false) noexcept;

		virtual ~surface();

		/**
		 * @brief Create VKDT Surface
		 *
		 * @param allocator Vulkan Memory Allocator
		 */
		void createVKDTSurface(VkAllocationCallbacks* allocator = nullptr);

	private:

		//Vulkan Memory Allocator
		VkAllocationCallbacks* pAllocator;

	protected:

		//Debugging Variables
		bool debug{};
		bool verbose{};

		//Vulkan Surface
		VkSurfaceKHR vkdtVKSurface;

	};
}