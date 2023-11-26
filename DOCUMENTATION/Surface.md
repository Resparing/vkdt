# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Surface is a abstraction over the Vulkan Surface KHR, it is found in the `vkdt/surface.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught & debugged with a try-catch & `const std::exception&`.

<br>

### Requirements

Almost all functions of the VKDT Surface require a valid VKDT Window & VKDT Instance to be setup. Refer to their respective documentations for more information.

<br>

### Adding VKDT Surface Header

Use the following include statement to include the Surface file:
```cpp
#include <vkdt/surface.h>
```

<br>

### Setup of VKDT Surface

1. Create VKDT Surface pointer:
	```cpp
	vkdt::surface::surface* pVKDTSurface;
	```

2. Configure `debug` & `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable is used for debugging the VKDT Surface creation status. The `verbose` variable can be used to check what stage the VKDT Surface is at & also debug allocation & de-allocation methods.

3. Initialize VKDT Surface
	```cpp
	surface(const bool debug = false, const bool verbose = false) noexcept;
	```

	- There are 2 parameters required:
		2. `debug` Whether to allow debugging in messages.
		3. `verbose` Allow general & verbose debugging methods in messages.

4. Create VKDT Surface:
	```cpp
	void createVKDTSurface(VkAllocationCallbacks* allocator = nullptr);
	```

	- The VKDT Surface will be created, & all extensions & layers will be checked.

	- There is 1 parameter:
		1. `allocator` A Vulkan memory allocator.

<br>

### Deletion Function

Call the following function for deleting the VKDT Surface & destroying all resources.

```cpp
~surface();
```

<br>

### Finished VKDT Surface Code

```cpp
vkdt::surface::surface* pVKDTSurface;

this -> createWindow();
this -> createInstance();

pVKDTSurface = new vkdt::surface::surface(true, true);
pVKDTSurface -> createVKDTSurface(nullptr);

...

delete pVKDTSurface;

this -> destroyInstance();
this -> destroyWindow();
```