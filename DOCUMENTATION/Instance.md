# DOCUMENTATION

A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Instance is a abstraction over the Vulkan Instance, it is found in the `vkdt/instance.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`.

<br>

### Requirements
The VKDT Instance does not need any Options to be setup

<br>

### Adding VKDT Instance Header

Use the following include statement to include the instance file, as well as the necessary `vkdt/_instanceStruct.h` header file
```cpp
#include <vkdt/instance.h>
```

<br>

### Setup of VKDT Instance

1. Create VKDT Instance pointer
	```cpp
	vkdt::instance::instance* pVKDTInstance;
	```

2. Create & Setup an instance of an VKDT Instance Application Data Struct
	1. Initialize application data struct
		```cpp
		vkdt::instance::applicationData appData{};
		```

	2. Set the name of your application
		```cpp
		vkdt::instance::applicationData appData
		{
			.name = "SAMPLE NAME",
		};
		```

	3. Initialize the version portion of your application struct. Note that this does not affect the selected Vulkan Instance Version
		```cpp
		vkdt::instance::applicationData appData
		{
			.name = "SAMPLE NAME",

			.version =
			{

			},
		};
		```

	4. Set the version portion of your application struct. Note that this does not affect the selected Vulkan Instance Version
		- The `patch` is the ID of the different type of application
		- The `major` is your current version
		- The `minor` is your update version
		- The `variant` is your fixed version
		```cpp
		vkdt::instance::applicationData appData
		{
			.name = "SAMPLE NAME",

			.version =
			{
				.patch = 0,

				.major = 1,
				.minor = 15,
				.variant = 98,
			},
		};
		```

3. Configure `debug` and `verbose` variables
	- These variables are for printing information to the stdout. The `debug` variable is used for debugging what part of the Vulkan instance creation process VKDT is currently at. The `verbose` variable can be used to help check if VKDT has setup the Vulkan instance properly. These variables **do not** affect the error handling that VKDT will do.

4. Call the Instance Creation Function
	```cpp
	instance
	(
		const vkdt::instance::applicationData& applicationInfo,
		const bool debug = false,
		const bool verbose = false
	) noexcept;
	```

	- The VKDT Instance will receive the application information, parse it and debug some information based

	- There are 3 parameters:
		1. `applicationInfo` A const reference to your application data, defined in step 3
		2. `debug` A const boolean to allow debugging.
		3. `verbose` A const boolean to allow information on what is happening in the VKDT Instance. Note that this option will also add debugging to the Vulkan instance creation and destruction functions.

5. Get a vector of your requested Vulkan Extensions & Layers
	- The vector must be type `std::vector<const char*>`

	- When you want to request an extension / layer, add the extension / layer name to the vector
		```cpp
		std::vector<const char*> requestedExtensions =
		{
			"VK_EXTENSION_NAME"
		};
		```

	- If you do not request any extensions / layers, use a `{}` in the function parameters

6. Setup VKDT Instance
	```cpp
	void setupVKDTInstance
	(
		const std::vector<const char*>& vkdtRequestedExtensions = {},
		const std::vector<const char*>& vkdtRequestedLayers = {}
	);
	```

	- The VKDT Instance will start setting itself and fill out the important vector

	- There are 2 parameters:
		1. `vkdtRequestedExtensions` A Reference to a `std::vector<const char*>` of requested Vulkan Extensions
		2. `vkdtRequestedLayers` A Reference to a `std::vector<const char*>` of requested Vulkan Layers

6. Create VKDT Instance
	```cpp
	void createVKDTInstance(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);
	```

	- The VKDT Instance will be created, and all extensions & layers will be checked

	- There is 1 parameter:
		1. `allocator` A Vulkan memory allocator

<br>

### Deletion Function

Call the following function for deleting VKDT and destroying all resources

```cpp
virtual ~instance();
```

The following function will delete the VKDT Instance, and destroy all resources

<br>

### Finished VKDT Instance Code

```cpp
//Application Information
vkdt::instance::applicationData appInfo =
{
	//Application Name
	.name = "Test Engine",

	//Application Version
	.version =
	{
		.patch = 0,

		.major = 1,
		.minor = 15,
		.variant = 98,
	},
};

//Allocate VKDT Instance
vkdt::instance::instance pVKDTInstance = new vkdt::instance::instance(appInfo, true, true);

//Setup VKDT Instance
pVKDTInstance -> setupVKDTInstance({}, {});
pVKDTInstance -> createVKDTInstance(nullptr);

...

delete pVKDTInstance;
```