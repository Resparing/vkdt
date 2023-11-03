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
		GPU(vkdt::instance::instance* vkdtInstance, const bool debug = false, const bool verbose = false) noexcept;

		virtual ~GPU();

		/**
		 * @brief Create a VKDT GPU
		 *
		 * @param vkdtGPUName Name of GPU to Force Request
		 */
		void findVKDTGPU(const char* vkdtGPUName = "");

		/**
		 * @brief Get a Reference to VKDT Vulkan Physical Device
		 *
		 * @attention Use for Extending VKDT GPU Class and for Internal Use!
		 *
		 * @return Reference to VKDT Vulkan Physical Device
		 */
		const VkPhysicalDevice& refVKPhysicalDevice(void) const noexcept;

	private:

		/**
		 * @brief Check if Vulkan Device is Suitable for VKDT
		 */
		bool isVKDTGPUSuitable(const VkPhysicalDevice& vkdtVKSelectedPhysicalDevice) const noexcept;

	protected:

		//Vulkan Instance Pointer & Physical Device
		VkInstance* pVVKInstance;
		VkPhysicalDevice vkdtVKPhysicalDevice = VK_NULL_HANDLE;

		//Debug Variables
		bool debug{};
		bool verbose{};

	};
}