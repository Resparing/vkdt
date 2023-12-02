# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Image View is an abstraction over a C-Array of Vulkan Image View, it is found in the `vkdt/imageView.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught & debugged with a try-catch & `const std::exception&`.

<br>

### Requirements

Almost all functions of the VKDT Image View require a valid VKDT Logical Device & VKDT Swapchain to be setup. Refer to the Logical Device & Swapchain Documentation on how to set those up.

<br>

### Adding VKDT Image View Header

Use the following include statement to include the Image View file:
```cpp
#include <vkdt/imageView.h>
```

<br>

### Setup of VKDT Image View

1. Create VKDT Image View pointer:
	```cpp
	vkdt::imageView::imageView* pVKDTImageView;
	```

2. Configure `debug` & `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable is used for debugging the VKDT Image View creation status. The `verbose` variable is used for debugging initialization, deletion & stage of Image View creation process.

3. Initialize VKDT Image View:
	```cpp
	imageView(const bool debug = false, const bool verbose = false) noexcept;
	```

	- There are 2 parameters required:
		1. `debug` Whether to allow debugging in messages.
		2. `verbose` Allow general & verbose debugging methods in messages.

	- The `imageView()` function must be called **before** the VKDT Swapchain is created.

4. Create VKDT Image View:
	```cpp
	void createVKDTImageView(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);
	```

	- All VKDT Image View will be created and get added to a vector.

	- There is 1 parameter:
		1. `allocator` A Vulkan memory allocator.

	- The `createVKDTImageView()` function must be called **after** the VKDT Swapchain is created

<br>

### Deletion Function

Call the following function for deleting the VKDT Image View & destroying all resources.

```cpp
~imageView();
```

<br>

### Finished VKDT Image View Code

```cpp
#include <vkdt/imageView.h>

vkdt::imageView::imageView* pVKDTImageView;

this -> createDevice();

pVKDTImageView = new vkdt::imageView::imageView(true, true);

this -> createSwapchain();

pVKDTImageView -> createVKDTImageView(nullptr);

...

delete pVKDTImageView;

this -> destroySwapchain();
this -> destroyDevice();
```