# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Frame Buffer is an abstraction over a C-Array of Vulkan Frame Buffer, it is found in the `vkdt/framebuffer.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught & debugged with a try-catch & `const std::exception&`.

<br>

### Requirements

Almost all functions of the VKDT Frame Buffer require a valid VKDT Logical Device & VKDT Swapchain to be setup. Refer to the Logical Device & Swapchain documentation on how to set those up.

<br>

### Adding VKDT Frame Buffer Header

Use the following include statement to include the Frame Buffer file:
```cpp
#include <vkdt/framebuffer.h>
```

<br>

### Setup of VKDT Frame Buffer

1. Create VKDT Frame Buffer pointer:
	```cpp
	vkdt::framebuffer::framebuffer* pVKDTFramebuffer;
	```

2. Configure `debug` & `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable is used for debugging the complete VKDT Frame Buffer creation status. The `verbose` variable is used for debugging initialization, deletion & number of Frame Buffer successful creations.

3. Initialize VKDT Frame Buffer:
	```cpp
	framebuffer(const bool debug = false, const bool verbose = false) noexcept;
	```

	- There are 2 parameters required:
		1. `debug` Whether to allow debugging in messages.
		2. `verbose` Allow general & verbose debugging methods in messages.

4. Create VKDT Frame Buffer:
	```cpp
	void createVKDTFramebuffer(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);
	```

	- All VKDT Frame Buffer will be created and get added to a vector.

	- There is 1 parameter:
		1. `allocator` A Vulkan memory allocator.

<br>

### Deletion Function

Call the following function for deleting the VKDT Frame Buffer & destroying all resources.

```cpp
~framebuffer();
```

<br>

### Finished VKDT Frame Buffer Code

```cpp
#include <vkdt/framebuffer.h>

vkdt::framebuffer::framebuffer* pVKDTFramebuffer;

this -> createDevice();
this -> createSwapchain();

pVKDTFramebuffer = new vkdt::framebuffer::framebuffer(true, true);
pVKDTFramebuffer -> createVKDTFramebuffer(nullptr);

...

delete pVKDTFramebuffer;

this -> destroySwapchain();
this -> destroyDevice();
```