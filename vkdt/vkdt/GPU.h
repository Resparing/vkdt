//Header Guard
#pragma once

//Include Headers
#include <vkdt/_vkdtConfig.h>
#include <vkdt/instance.h>

namespace vkdt::GPU
{
	class GPU
	{
	public:

		/**
		 * @brief Create VKDT GPU
		 *
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		GPU(const bool debug = false, const bool verbose = false) noexcept;

		virtual ~GPU();

		/**
		 * @brief Create a VKDT GPU
		 *
		 * @param vkdtGPUName C-String Name of GPU to Force Request
		 */
		void findVKDTGPU(const char* vkdtGPUName = "");

	private:

		/**
		 * @brief Check if Vulkan Device is Suitable for VKDT
		 *
		 * @param vkdtVKSelectedPhysicalDevice Vulkan Physical Device to Check
		 */
		bool isVKDTGPUSuitable(const VkPhysicalDevice& vkdtVKSelectedPhysicalDevice) const noexcept;

	protected:

		//Vulkan Physical Device
		VkPhysicalDevice vkdtVKPhysicalDevice = VK_NULL_HANDLE;

		//Debug Variables
		bool debug{};
		bool verbose{};

	};
}