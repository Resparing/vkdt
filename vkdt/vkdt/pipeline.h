//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>

namespace vkdt::pipeline
{
	class pipeline
	{
	public:

		/**
		 * @brief Initialize VKDT Pipeline
		 *
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		pipeline
		(
			const bool debug = false,
			const bool verbose = false
		) noexcept;

		~pipeline();

		/**
		 * @brief Create VKDT Pipeline
		 *
		 * @param vertexShaderPath Path to SPIR-V Vertex Shader Bytecode
		 * @param fragmentShaderPath Path to SPIR-V Fragment Shader Bytecode
		 * @param allocator Vulkan Memory Allocator
		 */
		void createVKDTPipeline
		(
			const std::string& vertexShaderPath = "",
			const std::string& fragmentShaderPath = "",
			VkAllocationCallbacks* allocator = VK_NULL_HANDLE
		);

	private:

		//Vulkan Memory Allocator
		VkAllocationCallbacks* pAllocator;

		//Vulkan Pipeline Layout
		VkPipelineLayout vkdtVKPipelineLayout;

		//Vulkan Render Pass
		VkRenderPass vkdtVKRenderpass;

		/**
		 * @brief Read a File
		 *
		 * @param path The Path of Requested File
		 *
		 * @return A Character Vector of File Contents
		 */
		std::vector<char> readFile(const std::string& path = "") const;

		/**
		 * @brief Create Shader Module
		 *
		 * @param byteCode A Reference to a Character Vector of Shader Bytecode
		 * @param allocator Vulkan Memory Allocator
		 *
		 * @return Correctly Initialized Vulkan Shader Module
		 */
		VkShaderModule createVKShaderModule(const std::vector<char>& byteCode = {});

	protected:

		//Vulkan Pipeline
		VkPipeline vkdtVKPipeline;

		//Debugging Variables
		bool debug{};
		bool verbose{};

	};
}