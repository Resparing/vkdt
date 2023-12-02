# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Queue is an abstraction over the Vulkan Queue, it is found in the `vkdt/queue.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught & debugged with a try-catch & `const std::exception&`.

<br>

### Requirements

The VKDT Queue does not need any Objects to be setup.

<br>

### Adding VKDT Queue Header

Use the following include statement to include the Queue file:
```cpp
#include <vkdt/debug.h>
```

<br>

### Setup of VKDT Queue

1. Create VKDT Queue pointer:
	```cpp
	vkdt::queue::queue* pVKDTQueue;
	```

2. Configure `debug` & `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable currently does not do anything. The verbose variable can be used to see if the Queue was initialized properly

3. Initialize VKDT Queue:
	```cpp
	queue(const bool debug = false, const bool verbose = false);
	```

	- There are 2 parameters required:
		1. `debug` Whether to allow debugging in messages.
		2. `verbose` Allow general & verbose debugging methods in messages.

<br>

### Deletion Function

Call the following function for deleting the VKDT Queue & destroying all resources.

```cpp
~queue();
```

<br>

### Finished VKDT Queue Code

```cpp
#include <vkdt/queue.h>

vkdt::queue::queue* pVKDTQueue;

pVKDTQueue = new vkdt::queue::queue(true, true);

...

delete pVKDTQueue;

```