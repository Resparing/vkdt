//Include Header File
#include <vkdt/pipeline.h>

//Include Headers
#include <_vkdt/pObjects.h>

vkdt::pipeline::pipeline::pipeline(const bool debug, const bool verbose) noexcept : debug(debug), verbose(verbose)
{
	//Set Pointer to Vulkan Pipeline, Renderpass & Pipeline Layout
	_vkdt::pObjects::pVKPipeline = &this -> vkdtVKPipeline;
	_vkdt::pObjects::pVKRenderPass = &this -> vkdtVKRenderpass;
	_vkdt::pObjects::pVKPipelineLayout = &this -> vkdtVKPipelineLayout;

	//Debug Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized VKDT Pipeline!\n";
	}
}

vkdt::pipeline::pipeline::~pipeline()
{
	//Destroy Vulkan Pipeline, Pipeline Layout & Renderpass
	vkDestroyPipeline(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKPipeline, this -> pAllocator);
	vkDestroyPipelineLayout(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKPipelineLayout, this -> pAllocator);
	vkDestroyRenderPass(*_vkdt::pObjects::pVKLogicalDevice, this -> vkdtVKRenderpass, this -> pAllocator);

	//Debug Deletion Success
	if(this -> verbose)
	{
		std::cout << "Successfully Destroyed VKDT Pipeline!\n";
	}
}

void vkdt::pipeline::pipeline::createVKDTPipeline
(
	const std::string& vertexShaderPath,
	const std::string& fragmentShaderPath,
	VkAllocationCallbacks* allocator
)
{
	//Set Vulkan Allocator
	this -> pAllocator = allocator;

	//Render Pass Description Struct
	VkAttachmentDescription colorAttachmentDescription =
	{
		//Swapchain Image Format
		.format = *_vkdt::pObjects::pVKSurfaceFormat,

		//Disable Multisampling
		.samples = VK_SAMPLE_COUNT_1_BIT,

		//What to do When Loading & Storing Data in the Frame Buffer
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,  //Clear the Values Beforehand
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,  //Store Contents of Frame to Present Later

		//What to do when Loading & Storing Stencil Data in the Frame Buffer
		.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,  //Don't do anything with Stencil Data
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,  //Don't do anything with Stencil Data

		//Don't Care about Previous Surface Layout
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,

		//Images to Present in the Swapchain
		.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
	};

	//Debug Render Pass Description Success
	if(this -> verbose)
	{
		std::cout << "Successfully Described Vulkan Renderpass Attachment!\n";
	}

	//Vulkan Color Attachment Reference Struct
	VkAttachmentReference colorAttachmentReference =
	{
		//Index of Vulkan Renderpass Attachment
		.attachment = 0,

		//Give Best Performance
		.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	};

	//Vulkan Pipeline Subpass
	VkSubpassDescription subpass =
	{
		//Subpass Type
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,

		//Color Attachment References
		.colorAttachmentCount = 1,
		.pColorAttachments = &colorAttachmentReference,
	};

	//Vulkan Subpass Dependency Struct
	VkSubpassDependency subpassDependency =
	{
		//Indexes of Vulkan Dependency & Dependent Subpass
		.srcSubpass = VK_SUBPASS_EXTERNAL,
		.dstSubpass = 0,

		//Wait for Vulkan Swap Chain to Finish Reading Image Before Accessing
		.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.srcAccessMask = 0,

		//Prevent Transition from Color Attachment to Writing Color Attachment Until Needed
		.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
	};

	//Vulkan Pipeline Renderpass Creation Information Struct
	VkRenderPassCreateInfo renderPassCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,

		//Pipeline Color Attachment Information
		.attachmentCount = 1,
		.pAttachments = &colorAttachmentDescription,

		//Pipeline Subpass Information
		.subpassCount = 1,
		.pSubpasses = &subpass,

		//Dependencies
		.dependencyCount = 1,
		.pDependencies = &subpassDependency,
	};

	//Create Vulkan Renderpass
	const VkResult createVKRenderpassResult = vkCreateRenderPass
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		&renderPassCreateInfo,
		this -> pAllocator,
		&this -> vkdtVKRenderpass
	);

	if(createVKRenderpassResult == VK_SUCCESS)
	{
		//Debug Vulkan Pipeline Renderpass Creation Success
		if(this -> verbose)
		{
			std::cout << "Successfully Created Vulkan Pipeline Renderpass!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create Vulkan Pipeline Renderpass! Error: " + std::to_string(createVKRenderpassResult) + "!\n");
	}

	//Load Bytecode of Vertex & Fragment Shaders
	const std::vector<char> vertBytecode = this -> readFile(vertexShaderPath);
	const std::vector<char> fragBytecode = this -> readFile(fragmentShaderPath);

	if(this -> debug || this -> verbose)
	{
		std::cout << "Successfully Loaded Vertex & Fragment Bytecode!\n";
	}

	//Create Vulkan Vertex & Fragment Shader Modules
	VkShaderModule vertShaderModule = this -> createVKShaderModule(vertBytecode);
	VkShaderModule fragShaderModule = this -> createVKShaderModule(fragBytecode);

	//Vulkan Vertex Shader Stage Creation Information Struct
	VkPipelineShaderStageCreateInfo vertShaderStageInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,

		//Type of Shader
		.stage = VK_SHADER_STAGE_VERTEX_BIT,

		//Shader Module
		.module = vertShaderModule,

		//Main Function
		.pName = "main",
	};

	//Vulkan Fragment Shader Stage Creation Information Struct
	VkPipelineShaderStageCreateInfo fragShaderStageInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,

		//Type of Shader
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,

		//Shader Module
		.module = fragShaderModule,

		//Main Function
		.pName = "main",
	};

	//Array of Shader Creation Information Structs
	std::array<VkPipelineShaderStageCreateInfo, 2> shaderCreateInfos = {vertShaderStageInfo, fragShaderStageInfo};

	//Debug Shader Stage Create Info Success
	if(this -> verbose)
	{
		std::cout << "Successfully Loaded Vulkan Shader Module Functions!\n";
	}

	//Allow Dynamic States
	std::vector<VkDynamicState> vkdtVKDynamicStates =
	{
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	//Vulkan Pipeline Dynamic State Creation Information Struct
	VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,

		//Dynamic State Options
		.dynamicStateCount = static_cast<uint32_t>(vkdtVKDynamicStates.size()),  //Vulkan Dynamic States Number
		.pDynamicStates = vkdtVKDynamicStates.data(),  //Vulkan Dynamic States Array
	};

	//Debug Dynamic State Initialization Success
	if(this -> verbose)
	{
		std::cout << "Successfully Initialized Vulkan Pipeline Dynamic States!\n";
	}

	//Vertex Input Information Creation Information Struct
	VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,

		//!TEMPORARY
		.vertexBindingDescriptionCount = 0,
		.vertexAttributeDescriptionCount = 0,
		.pVertexBindingDescriptions = nullptr,
		.pVertexAttributeDescriptions = nullptr,
	};

	//Vulkan Pipeline Input Assembly Creation Information Struct, Needed to Describe the Geometry Drawn from Vertexes
	VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,

		//Setting to Draw Triangles
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE,
	};

	//Debug Vulkan Pipeline Input Assembly Initialization
	if(this -> verbose)
	{
		std::cout << "Successfully Created Vulkan Pipeline Input Assembly Information!\n";
	}

	//Vulkan Pipeline Viewport
	VkViewport vkdtVKViewport =
	{
		//Start Region
		.x = 0,
		.y = 0,

		//End Region
		.width = static_cast<float>(_vkdt::pObjects::pVKSurfaceExtent -> width),
		.height = static_cast<float>(_vkdt::pObjects::pVKSurfaceExtent -> height),

		//Default Depth Values
		.minDepth = 0.0f,
		.maxDepth = 1.0f,
	};

	//Debug Viewport Initialization Success
	if(this -> verbose)
	{
		std::cout																			\
		<< "Successfully Created Vulkan Viewport with Width: " << vkdtVKViewport.width		\
		<< ", Height: " << vkdtVKViewport.height << "!\n";
	}

	//Vulkan Pipeline Scissor
	VkRect2D vkdtVKScissor =
	{
		//Disable Offset
		.offset = {0, 0},

		//Framebuffer Size
		.extent = *_vkdt::pObjects::pVKSurfaceExtent,
	};

	//Vulkan Pipeline Viewport Creation Information Struct
	VkPipelineViewportStateCreateInfo viewportStateCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,

		//Vulkan Viewports
		.viewportCount = 1,
		.pViewports = &vkdtVKViewport,

		//Vulkan Scissors
		.scissorCount = 1,
		.pScissors = &vkdtVKScissor,
	};

	//Vulkan Pipeline Rasterization Creation Information Struct
	VkPipelineRasterizationStateCreateInfo rasterizerCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,

		//Disabled to not Enable GPU Features
		.depthClampEnable = VK_FALSE,

		//Allow Frame to be Rasterized
		.rasterizerDiscardEnable = VK_FALSE,

		//How to filly Polygons
		.polygonMode = VK_POLYGON_MODE_FILL,

		//Thickness of Lines in Fragment Count
		.lineWidth = 1.0f,

		//Culling Mode
		.cullMode = VK_CULL_MODE_BACK_BIT,

		//How Vertex Data is Given
		.frontFace = VK_FRONT_FACE_CLOCKWISE,

		//Disable Depth Information
		.depthBiasEnable = VK_FALSE,
	};

	//Vulkan Pipeline Multisampling
	VkPipelineMultisampleStateCreateInfo multisampleCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,

		//Enable Multisampling
		.sampleShadingEnable = VK_FALSE,

		//Number of Samples
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
	};

	//Vulkan Pipeline Color Blend Information
	VkPipelineColorBlendAttachmentState colorBlendAttachment =
	{
		//Color to Blend
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,

		//Disable Color Blending
		.blendEnable = VK_FALSE,
	};

	//Vulkan Pipeline Color Blend Creation Information
	VkPipelineColorBlendStateCreateInfo colorBlendCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,

		//Bitwise Color Blending
		.logicOpEnable = VK_FALSE,

		//Color Attachment
		.attachmentCount = 1,
		.pAttachments = &colorBlendAttachment,
	};

	//Vulkan Pipeline Layout Creation Information Struct
	VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
	};

	//Create Vulkan Pipeline Layout
	const VkResult createVKPipelineLayoutResult = vkCreatePipelineLayout
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		&pipelineLayoutCreateInfo,
		this -> pAllocator,
		&this -> vkdtVKPipelineLayout
	);

	if(createVKPipelineLayoutResult == VK_SUCCESS)
	{
		//Debug Creation Success
		if(this -> verbose)
		{
			std::cout << "Successfully Initialized Vulkan Pipeline Layout!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create Vulkan Pipeline Layout! Error: " + std::to_string(createVKPipelineLayoutResult) + "!\n");
	}

	//Vulkan Pipeline Creation Information Struct
	VkGraphicsPipelineCreateInfo pipelineCreateInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,

		//Stage Information
		.stageCount = static_cast<uint32_t>(shaderCreateInfos.size()),
		.pStages = shaderCreateInfos.data(),

		//Pointers to Fixed Function Stages
		.pInputAssemblyState = &pipelineInputAssemblyStateCreateInfo,
		.pRasterizationState = &rasterizerCreateInfo,
		.pVertexInputState = &pipelineVertexInputStateCreateInfo,
		.pMultisampleState = &multisampleCreateInfo,
		.pColorBlendState = &colorBlendCreateInfo,
		.pViewportState = &viewportStateCreateInfo,
		.pDynamicState = &dynamicStateCreateInfo,

		//Fixed Function Pipeline Layout
		.layout = this -> vkdtVKPipelineLayout,

		//Render Pass
		.renderPass = this -> vkdtVKRenderpass,

		//Index of Subpass where the Pipeline will be Used
		.subpass = 0,
	};

	//Create Vulkan Graphics Pipeline
	const VkResult createVKPipelineResult = vkCreateGraphicsPipelines
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		VK_NULL_HANDLE,
		1, &pipelineCreateInfo,
		this -> pAllocator,
		&this -> vkdtVKPipeline
	);

	if(createVKPipelineResult == VK_SUCCESS)
	{
		//Debug Pipeline Creation Success
		if(this -> debug || this -> verbose)
		{
			std::cout << "Successfully Created VKDT Pipeline!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create Vulkan Pipeline! Error: " + std::to_string(createVKPipelineResult) + "!\n");
	}

	//Destroy Vulkan Vertex & Fragment Shader Modules
	vkDestroyShaderModule(*_vkdt::pObjects::pVKLogicalDevice, fragShaderModule, this -> pAllocator);
	vkDestroyShaderModule(*_vkdt::pObjects::pVKLogicalDevice, vertShaderModule, this -> pAllocator);
}

std::vector<char> vkdt::pipeline::pipeline::readFile(const std::string& path) const
{
	//Get Input File
	std::ifstream file(path, std::ios::binary);

	//Check if File was Created Successfully
	if(!file.is_open())
	{
		throw std::runtime_error("Failed to Load File at: \"" + path + "\"!\n");
	}
	else
	{
		//Debug File Load Success
		if(this -> verbose)
		{
			std::cout << "Successfully Loaded File at: \"" << path << "\"!\n";
		}
	}

	//Get Length of File
	file.seekg(0, std::ios::end);
	std::streamsize fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	//Vector of File Information
	std::vector<char> contents(static_cast<size_t>(fileSize));

	//Read File into Vector
	file.read(contents.data(), fileSize);

	//Close File
	file.close();

	//Debug File Read Success
	if(this -> verbose)
	{
		std::cout << "Successfully Read File at: \"" << path << "\"!\n";
	}

	return contents;
}

VkShaderModule vkdt::pipeline::pipeline::createVKShaderModule(const std::vector<char>& byteCode)
{
	//Vulkan Shader Module Object
	VkShaderModule shaderModule;

	//Vulkan Shader Module Creation Information Struct
	VkShaderModuleCreateInfo createInfo =
	{
		//Struct Type
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,

		//Bytecode Size
		.codeSize = byteCode.size(),

		//Bytecode
		.pCode = reinterpret_cast<const uint32_t*>(byteCode.data()),
	};

	//Create Vulkan Shader Module
	const VkResult createVKShaderModuleResult = vkCreateShaderModule
	(
		*_vkdt::pObjects::pVKLogicalDevice,
		&createInfo,
		this -> pAllocator,
		&shaderModule
	);

	if(createVKShaderModuleResult == VK_SUCCESS)
	{
		//Debug Creation Success
		if(this -> debug || this -> verbose)
		{
			std::cout << "Successfully Created Vulkan Shader Module!\n";
		}
	}
	else
	{
		throw std::runtime_error("Failed to Create Vulkan Shader Module! Error: " + std::to_string(createVKShaderModuleResult) + "!\n");
	}

	return shaderModule;
}