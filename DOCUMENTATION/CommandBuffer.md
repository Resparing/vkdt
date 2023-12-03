# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Command Buffer is an abstraction over Vulkan Command Buffer & vectors of Vulkan Command Pools, it is found in the `vkdt/commandbuffer.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught & debugged with a try-catch & `const std::exception&`.

<br>

### Requirements

Almost all functions of the VKDT Command Buffer require a valid VKDT Logical Device, VKDT Swapchain, & VKDT Pipeline to be setup. Refer to their respective documentation on how to set those up.

<br>

### Adding VKDT Command Buffer Header

Use the following include statement to include the Command Buffer file:
```cpp
#include <vkdt/commandbuffer.h>
```

<br>

### Setup of VKDT Command Buffer

1. Create VKDT Command Buffer pointer:
	```cpp
	vkdt::commandbuffer::commandbuffer* pVKDTCommandBuffer;
	```

2. Configure `debug` & `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable is used for debugging the complete VKDT Command Buffer creation status. The `verbose` variable is used for debugging initialization, deletion & stage of Command Buffer successful creations.

3. Initialize VKDT Command Buffer:
	```cpp
	commandbuffer(const bool debug = false, const bool verbose = false) noexcept;
	```

	- There are 2 parameters required:
		1. `debug` Whether to allow debugging in messages.
		2. `verbose` Allow general & verbose debugging methods in messages.

4. Create VKDT Command Buffer:
	```cpp
	void createVKDTCommandbuffer(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);
	```

	- There is 1 parameter:
		1. `allocator` A Vulkan memory allocator.

<br>

### Deletion Function

Call the following function for deleting the VKDT Command Buffer & destroying all resources.

```cpp
~commandbuffer();
```

<br>

### Finished VKDT Command Buffer Code

```cpp
#include <vkdt/commandbuffer.h>

vkdt::commandbuffer::commandbuffer* pVKDTCommandBuffer;

this -> createDevice();
this -> createSwapchain();
this -> createPipeline();

pVKDTCommandBuffer = new vkdt::commandbuffer::commandbuffer(true, true);
pVKDTCommandBuffer -> createVKDTCommandbuffer(nullptr);

...

delete pVKDTCommandBuffer;

this -> destroyPipeline();
this -> destroySwapchain();
this -> destroyDevice();
```