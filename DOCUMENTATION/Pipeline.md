# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Pipeline is an abstraction over the Vulkan Pipeline Layout, Vulkan Renderpass, & Vulkan Pipeline. It is found in the `vkdt/pipeline.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught & debugged with a try-catch & `const std::exception&`.

<br>

### Requirements

Almost all functions of the VKDT Pipeline require a valid VKDT Device & VKDT Swapchain. Refer their respective documentation on how to set those up.

<br>

### Compile SPIR-V Shaders

The Vulkan SDK will provide the compiler for your shaders called `glslc`. It should be in the binary directory. It is like the c++ compilers. The syntax is the following:
```zsh
/path/to/glslc shader.vert -o bin/vert.spv
```

This should compile your vertex shader called `shader.vert` into a spir-v file called `vert.spv` in the `bin` directory. Make sure to do this with your fragment shaders as well.

<br>

### Adding VKDT Pipeline Header

Use the following include statement to include the Pipeline file:
```cpp
#include <vkdt/pipeline.h>
```

<br>

### Setup of VKDT Pipeline

1. Create VKDT Pipeline pointer:
	```cpp
	vkdt::pipeline::pipeline* pVKDTPipeline;
	```

2. Configure `debug` & `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable debugs creation success & when the VKDT Swapchain successfully selects the correct object. The verbose variable can be used to see initialization, deletion, struct initialization, & file information.

3. Initialize VKDT Pipeline:
	```cpp
	pipeline(const bool debug = false,const bool verbose = false) noexcept;
	```

	- There are 2 parameters required:
		1. `debug` Whether to allow debugging in messages.
		2. `verbose` Allow general & verbose debugging methods in messages.

3. Create VKDT Pipeline:
	```cpp
	void createVKDTPipeline
	(
		const std::string& vertexShaderPath = "",
		const std::string& fragmentShaderPath = "",
		VkAllocationCallbacks* allocator = VK_NULL_HANDLE
	);
	```

	- The VKDT Pipeline will be created, as well as the Vulkan Pipeline Layout & Vulkan Pipeline Renderpass.

	- There are 3 parameters:
		1. `vertexShaderPath` Path to the compiled Vertex Shader Bytecode relative to the current directory
		2. `fragmentShaderPath` Path to the compiled Fragment Shader Bytecode relative to the current directory
		3. `allocator` Vulkan Memory Allocator

<br>

### Deletion Function

Call the following function for deleting the VKDT Pipeline, destroying the Vulkan Pipeline Layout & Vulkan Renderpass and de-allocating all resources.

```cpp
~pipeline();
```

<br>

### Finished VKDT Pipeline Code

```cpp
#include <vkdt/pipeline.h>

vkdt::pipeline::pipeline* pVKDTPipeline;

this -> createDevice();
this -> createSwapchain();

pVKDTPipeline = new vkdt::pipeline::pipeline(true, true);
pVKDTPipeline -> createVKDTPipeline("bin/vert.spv", "bin/frag.spv", nullptr);

...

delete pVKDTPipeline;

this -> destroySwapchain();
this -> destroyDevice();
```