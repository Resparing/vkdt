# DOCUMENTATION

A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Debug is a abstraction over the Vulkan Debug Utils Messenger EXT, it is found in the `vkdt/debug.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`.

<br>

### Requirements
Some functions of the VKDT Debug Messenger require a valid VKDT Instance to be setup, refer to the Instance Documentation for how to setup the VKDT Instance

<br>

### Adding VKDT Instance Header

Use the following include statement to include the instance file, as well as the necessary `vkdt/debugFunction.h` header file
```cpp
#include <vkdt/debug.h>
```

<br>

### Setup of VKDT Debug Messenger

1. Create VKDT Debug Messenger pointer
	```cpp
	vkdt::debug::messenger* pVKDTDebugMessenger;
	```

2. Create callback function for VKDT Debug Messenger
	- The function needs to be static, have a return type of void and have the following parameters

	```cpp
	static void CALLBACK_FUNCTION
	(
		const vkdt::debug::messageSeverity messageSeverity,
		const vkdt::debug::messageType messageType,
		const vkdt::debug::messageData messageData
	);
	```

	- `messageSeverity` An enumeration of message severity debugged. This can be used to stop the debugging of unnecessary items by checking if the given severity is less than a selected severity: `if(messageSeverity <= vkdt::debug::messageSeverity::VERBOSE) return;`

	- `messageType` An enumeration of the message type debugged This can also be used to stop the debugging of unnecessary items by checking if the given message type is equal to a certain message type: `if(messageSeverity == vkdt::debug::messageType::VERBOSE) return;`

	- `messageData` A Struct containing important message data.
	```cpp
	//Message Data Struct
	struct messageData
	{
		//Message
		std::string message;

		//Message ID & Message ID Name
		int32_t messageID;
		std::string messageIDName;

		//Vector of Labels, Command Buffers & Objects
		std::vector<vkdt::debug::label> queueLabels;
		std::vector<vkdt::debug::label> commandBuffers;
		std::vector<vkdt::debug::object> objects;
	};
	```

	- The message data contains the message, the message ID name, and the message ID number
	- The message data also contains vectors of queue labels, command buffers, and objects
	- The message data contains vectors of queue labels, command buffers, and objects related to the callback
		- Queue Labels contain the label name and a color array
		- Command Buffers contain the command buffer name and a color array
		- Objects contain the object name, an enumeration of the object type, and a handle (pointer to the object as a number)

	- This is an example of a callback function:
		```cpp
		static void CALLBACK_FUNCTION
		(
			const vkdt::debug::messageSeverity messageSeverity,
			const vkdt::debug::messageType messageType,
			const vkdt::debug::messageData messageData
		)
		{
			if(messageSeverity <= vkdt::debug::messageSeverity::VERBOSE) return;
			if(messageSeverity == vkdt::debug::messageType::VERBOSE) return;

			std::cout << "\n[DEBUG][" << messageData.messageIDName << ":" << messageData.messageID << " ]" << messageData.message << "\n\n";
		}
		```
		- You can have more information than this, such as debugging the objects, but this is enough for most people.

3. Configure `debug` and `verbose` variables
	- These variables are for printing information to the stdout. The `debug` variable is used for debugging what part of the Vulkan instance creation process VKDT is currently at. The `verbose` variable can be used to check what stage the VKDT Debug Messenger is at

4. Initialize VKDT Debug Messenger
	```cpp
	messenger(vkdt::debug::vkdtCallback callbackFunc = VK_NULL_HANDLE, const bool debug = false, const bool verbose = false) noexcept;
	```

	- There are 3 parameters required:
		1. `callbackFunc` Function used by VKDT Debug Messenger Debugger
		2. `debug` Whether to Allow Debugging in Messages
		3. `verbose` Allow General & Verbose Debugging Methods in Messages

	- **ATTENTION** Make sure to call this function *before* creating your VKDT Instance if you are creating your instance with the `verbose` boolean on. If this did not happen, and you try creating your instance, an error will be thrown that you cannot create the instance without initializing your VKDT Debug Messenger

5. Create your VKDT Instance
	- This is the point where you are able to create your VKDT Instance without any errors popping up.

6. Create VKDT Debug Messenger
	```cpp
	void createVKDTDebugMessenger(VkAllocationCallbacks* allocator = VK_NULL_HANDLE);
	```

	- The VKDT Debug Messenger will be created, and all extensions & layers will be checked

	- There is 1 parameter:
		1. `allocator` A Vulkan memory allocator

<br>

### Deletion Function

Call the following function for deleting VKDT and destroying all resources

```cpp
virtual ~messenger() noexcept(false);
```

The following function will delete the VKDT Debug Messenger, and destroy all resources

<br>

### Finished VKDT Instance Code

```cpp
static void CALLBACK_FUNCTION
(
	const vkdt::debug::messageSeverity messageSeverity,
	const vkdt::debug::messageType messageType,
	const vkdt::debug::messageData messageData
)
{
	if(messageSeverity <= vkdt::debug::messageSeverity::VERBOSE) return;
	if(messageSeverity == vkdt::debug::messageType::VERBOSE) return;

	std::cout << "\n[DEBUG][" << messageData.messageIDName << ":" << messageData.messageID << " ]" << messageData.message << "\n\n";
}

vkdt::debug::messenger* pVKDTDebugMessenger;

pVKDTDebugMessenger = new vkdt::debug::messenger(CALLBACK_FUNCTION, true, true);

//Create your VKDT Instance - This does not need to be an OOP approach, but is recommended for RAII
this -> createInstance();

pVKDTDebugMessenger -> createVKDTDebugMessenger(nullptr);

...

delete pVKDTDebugMessenger;

//Destroy your VKDT Instance - Again this does not need to be an OOP approach
this -> destroyInstance();
```