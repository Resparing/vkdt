//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

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
		queue(const bool debug = false, const bool verbose = false) noexcept;

		~queue();

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