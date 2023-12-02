# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Device is an abstraction over the Vulkan Device, it is found in the `vkdt/device.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught & debugged with a try-catch & `const std::exception&`.

<br>

### Requirements

Almost all functions of the VKDT Device require a valid VKDT GPU & VKDT Queue to be setup. Refer to the GPU & Queue documentation on how to set those up.

<br>

### Adding VKDT Device Header

Use the following include statement to include the Device file:
```cpp
#include <vkdt/device.h>
```

<br>

### Setup of VKDT Device

1. Create VKDT Surface pointer:
	```cpp
	vkdt::device::device* pVKDTDevice;
	```

2. Configure `debug` & `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable is used for debugging information on the creation status of the VKDT GPU. The `verbose` variable can be used to check requested VKDT Extensions & Layers & information on parameters supplied.

3. Initialize VKDT Device:
	```cpp
	device
	(
		const std::vector<const char*>& vkdtVKRequestedExtensions = {},
		const std::vector<const char*>& vkdtVKRequestedLayers = {},
		const bool debug = false,
		const bool verbose = false
	) noexcept;
	```

	- There are 2 parameters required:
		1. `vkdtRequestedExtensions` A Reference to a `std::vector<const char*>` of requested Vulkan Device Extensions.
		2. `vkdtRequestedLayers` A Reference to a `std::vector<const char*>` of requested Vulkan Device Layers.
		3. `debug` Whether to allow debugging in messages.
		4. `verbose` Allow general & verbose debugging methods in messages.

4. Create VKDT Device:
	```cpp
	void createVKDTDevice(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);
	```

	- The VKDT Device will be created, & all extensions & layers will be added to it.

	- There is 1 parameter:
		1. `allocator` A Vulkan memory allocator.

<br>

### Deletion Function

Call the following function for deleting the VKDT Surface & destroying all resources.

```cpp
~device();
```

<br>

### Finished VKDT Surface Code

```cpp
#include <vkdt/device.h>

vkdt::device::device* pVKDTDevice;

this -> createGPU();
this -> createQueue();

pVKDTDevice = new vkdt::device::device({}, {}, true, true);
pVKDTDevice -> createVKDTSurface(nullptr);

...

delete pVKDTDevice;

this -> destroyGPU();
this -> destroyQueue();
```