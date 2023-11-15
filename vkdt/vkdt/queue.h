//Header Guard
#pragma once

//Include Headers
#include <vkdt/_vkdtConfig.h>

namespace vkdt::queue
{
	class queue
	{
	public:

		/**
		 * @brief Initialize VKDT Queue
		 *
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		queue(const bool debug, const bool verbose);

		virtual ~queue();

		/**
		 * @brief Get a Reference to VKDT Vulkan Queue
		 *
		 * @attention Use for Extending VKDT Queue Class and for Internal Use!
		 *
		 * @return Reference to Vulkan Queue
		 */
		const VkQueue& refVKQueue(void) const noexcept;

	private:
	protected:

		//Vulkan Queue
		VkQueue vkdtVKQueue;

		bool debug{};
		bool verbose{};

	};
}