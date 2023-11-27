# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT GPU is an abstraction over the Vulkan Physical Device, it is found in the `vkdt/GPU.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught & debugged with a try-catch & `const std::exception&`.

<br>

### Requirements

Almost all functions of the VKDT GPU require a valid VKDT Instance to be setup. Refer to the Instance documentation on how to setup the VKDT Instance.

<br>

### Adding VKDT GPU Header

Use the following include statement to include the GPU file:
```cpp
#include <vkdt/GPU.h>
```

<br>

### Setup of VKDT GPU

1. Create VKDT GPU pointer:
	```cpp
	vkdt::GPU::GPU* pVKDTGPU;
	```

2. Configure `debug` & `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable is used for debugging the VKDT GPU creation status. The `verbose` variable can be used to check what stage the VKDT Surface is at & also debug important information about found GPU's.

3. Initialize VKDT Surface
	```cpp
	GPU(const bool debug = false, const bool verbose = false) noexcept;
	```

	- There are 2 parameters required:
		2. `debug` Whether to allow debugging in messages.
		3. `verbose` Allow general & verbose debugging methods in messages.

4. Find VKDT GPU:
	```cpp
	void findVKDTGPU(const char* vkdtGPUName = "");
	```

	- The VKDT Surface will be created, & all extensions & layers will be checked.

	- There is 1 parameter:
		1. `vkdtGPU` An optional parameter which overwrites the selected VKDT GPU with a GPU of your choice. The way to do this requires that you give the VKDT GPU name to the function.

<br>

### Deletion Function

Call the following function for deleting the VKDT Surface & destroying all resources.

```cpp
~GPU();
```

Note that this function does not do anything at all, but is required to de-allocate the pointer created with the `new` keyword or `malloc()` function

<br>

### Finished VKDT GPU Code

```cpp
#include <vkdt/GPU.h>

vkdt::GPU::GPU* pVKDTGPU;

this -> createInstance();

pVKDTGPU = new vkdt::GPU::GPU(true, true);

...

this -> destroyInstance();

delete pVKDTGPU;
```