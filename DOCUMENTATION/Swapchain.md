# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Swapchain is an abstraction over the Vulkan Swapchain KHR, it is found in the `vkdt/swapchain.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught & debugged with a try-catch & `const std::exception&`.

<br>

### Requirements

Almost all functions of the VKDT Surface require a valid VKDT Device, VKDT GPU, VKDT Surface, VKDT Window & VKDT Image View to be setup. Refer their respective documentation on how to set those up.
<br>

### Adding VKDT Swapchain Header

Use the following include statement to include the Swapchain file:
```cpp
#include <vkdt/swapchain.h>
```

<br>

### Setup of VKDT Swapchain

1. Create VKDT Swapchain pointer:
	```cpp
	vkdt::swapchain::swapchain* pVKDTSwapchain;
	```

2. Configure `debug` & `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable debugs creation success & when the VKDT Swapchain successfully selects the correct object. The verbose variable can be used to see initialization, deletion, & when the Swapchain couldn't find an optimal object.

3. Initialize VKDT Swapchain
	```cpp
	swapchain(const bool debug = false, const bool verbose = false) noexcept;
	```

	- There are 2 parameters required:
		1. `debug` Whether to allow debugging in messages.
		2. `verbose` Allow general & verbose debugging methods in messages.

3. Create VKDT Swapchain
	```cpp
	void createVKDTSwapchain(VkAllocationCallbacks* allocator);
	```

	- The VKDT Swapchain will be created, as well as all objects

	- There is 1 parameter:
		1. `allocator` Vulkan Memory Allocator

<br>

### Deletion Function

Call the following function for deleting the VKDT Swapchain & destroying all resources.

```cpp
~swapchain();
```

<br>

### Finished VKDT Swapchain Code

```cpp
#include <vkdt/swapchain.h>

vkdt::swapchain::swapchain* pVKDTSwapchain;

this -> createDevice();
this -> createGPU();
this -> createSurface();
this -> createWindow();
this -> initImageView();

pVKDTSwapchain = new vkdt::swapchain::swapchain(true, true);
pVKDTSwapchain -> createVKDTSwapchain(nullptr);

...

delete pVKDTSwapchain;

this -> DestroyDevice();
this -> DestroyGPU();
this -> DestroySurface();
this -> DestroyWindow();
```