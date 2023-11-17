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

	private:
	protected:

		//Vulkan Queues
		VkQueue vkdtVKGraphicsQueue;
		VkQueue vkdtVKPresentQueue;

		//Debugging Variables
		bool debug{};
		bool verbose{};

	};
}