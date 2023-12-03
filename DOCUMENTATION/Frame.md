# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Frame is an abstraction over the Vulkan Semaphore (Image Available & Render Finished) & Vulkan Fence, it is found in the `vkdt/frame.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught & debugged with a try-catch & `const std::exception&`.

<br>

### Requirements

Almost all functions of the VKDT Frame require a valid VKDT Device, VKDT Swapchain, VKDT Command Buffer, VKDT Queue. Refer their respective documentation on how to set those up.

<br>

### Adding VKDT Frame Header

Use the following include statement to include the frame file:
```cpp
#include <vkdt/frame.h>
```

<br>

### Setup of VKDT Frame

1. Create VKDT Frame pointer:
	```cpp
	vkdt::frame::frame* pVKDTFrame;
	```

2. Configure `debug` & `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable is used for debugging the VKDT Frame setup status. The `verbose` variable is used for debugging initialization, deletion, stage of Frame setup process, & Frame stop success.

3. Initialize VKDT Frame:
	```cpp
	frame(const bool debug = false, const bool verbose = false) noexcept;
	```

	- There are 2 parameters required:
		1. `debug` Whether to allow debugging in messages.
		2. `verbose` Allow general & verbose debugging methods in messages.

4. Setup VKDT Frame:
	```cpp
	void setupVKDTFrame(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);
	```

	- The VKDT Frame will create all semaphores & fences

	- There is 1 parameter:
		1. `allocator` A Vulkan memory allocator.

<br>

### Deletion Function

Call the following function for deleting the VKDT Frame & destroying all resources.

```cpp
~frame();
```

<br>

### Main Loop Code

You can now draw the VKDT Frame in your main-loop code. This will record the VKDT Command Buffer, send information to the VKDT Queue, and set the Vulkan Semaphores. Let's pretend that `pVKDTWindow` is a pointer to the VKDT Window. You can now use the `drawVKDTFrame()` command to draw the frame. make sure that this is directly before or after the `update()` function. You should also make sure that you call the `stopVKDTFrame()` command directly after the main-loop code.

```cpp
while(pVKDTWindow -> isOpen())
{
	pVKDTWindow -> update();

	pVKDTFrame -> drawVKDTFrame();
}

pVKDTFrame -> stopVKDTFrame();
```

<br>

### Finished VKDT Frame Code

```cpp
#include <vkdt/frame.h>

vkdt::frame::frame* pVKDTFrame;

this -> createQueue();
this -> createDevice();
this -> createSwapchain();
this -> createCommandBuffer();

pVKDTFrame = new vkdt::frame::frame(true, true);
pVKDTFrame -> setupVKDTFrame(nullptr);

while(pVKDTWindow -> isOpen())
{
	pVKDTWindow -> update();

	pVKDTFrame -> drawVKDTFrame();

	...
}

pVKDTFrame -> stopVKDTFrame();

...

delete pVKDTFrame;

this -> destroyCommandBuffer();
this -> destroySwapchain();
this -> destroyDevice();
this -> destroyQueue();
```