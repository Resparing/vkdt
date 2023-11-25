# DOCUMENTATION

VKDT - A Vulkan Abstraction to Help Developers

<br>

### Introduction

The VKDT Window is a abstraction over the GLFW Window Pointer, it is found in the `vkdt/window.h` header file.
All debugging methods are printed with `std::cout`, all runtime errors are thrown with `throw std::runtime_error()`. These errors can be caught and debugged with a try-catch and `const std::exception&`.

<br>

### Requirements

The VKDT Window does not need any Objects to be setup.

<br>

### Adding VKDT Window Header

Use the following include statement to include the window file, as well as the necessary `vkdt/_windowEnum.h` header file.
```cpp
#include <vkdt/window.h>
```

<br>

### Setup of VKDT Window

1. Create VKDT Window Pointer:
	```cpp
	vkdt::window::window* pVKDTWindow;
	```

1. Setup VKDT Window Arguments:
	- VKDT Window Arguments is the VKDT way of setting up multiple arguments in VKDT. These are usually an unordered map of VKDT window arguments and VKDT window results.
	- You can create an instance of these using the following `const vkdt::window::windowArguments windowArgs = {};`.
	- You can then set arguments with the following code (Example disables resizing and maximizes the window).
	```cpp
	const vkdt::window::windowArguments windowArgs =
	{
		{vkdt::window::argument::RESIZABLE, vkdt::window::result::FALSE},
		{vkdt::window::argument::MAXIMIZED, vkdt::window::result::TRUE}
	};
	```

3. Configure `debug` and `verbose` variables:
	- These variables are for printing information to the stdout. The `debug` variable is used for debugging what part of the Vulkan Window creation process it is currently at. The `verbose` variable can be used to check what stage the VKDT Window is at and what the arguments are selected.

4. Initialize VKDT Window:
	```cpp
	window(const windowArguments windowArgs = {}, const bool debug = false, const bool verbose = false);
	```

	- There are 3 parameters required:
		1. `windowArgs` Arguments set by VKDT Window, use `{}` if there are no arguments.
		2. `debug` Whether to Allow Debugging in Messages.
		3. `verbose` Allow General & Verbose Debugging Methods in Messages.

5. Create your VKDT Window:
	```cpp
	void createWindow(const vkdt::window::size& windowSize = {800, 600}, const std::string& title = "");
	```
	- There are 2 parameters required:
		1. `windowSize` The size of the VKDT window.
			- When setting the following parameter, make sure to use `{WIDTH, HEIGHT}` as your window size, or use hard-coded numbers.
		2. `title` The name of the VKDT window.

<br>

### Deletion Function

Call the following function for deleting the VKDT Window and destroying all resources.

```cpp
virtual ~window();
```

<br>

### Main Loop Code

You can check if your window should stay open with the `isOpen()` function. The function will return a boolean whether the window should stay open or not. You **must** also update the window with the `update()` function. This is used to poll all events, and is important when rendering graphics. Use the following example as a reference.

```cpp
while(pVKDTWindow -> isOpen())
{
	pVKDTWindow -> update();

	...
}
```

<br>

### Finished VKDT Window Code

```cpp
const vkdt::window::windowArguments windowArgs =
{
	{vkdt::window::argument::RESIZABLE, vkdt::window::result::FALSE},
	{vkdt::window::argument::MAXIMIZED, vkdt::window::result::TRUE}
};

vkdt::window::window* pVKDTWindow;

pVKDTWindow = new vkdt::window::window(windowArgs, true, true);
pVKDTWindow -> createWindow({1000, 550}, "My VKDT Window");

...

while(pVKDTWindow -> isOpen())
{
	pVKDTWindow -> update();

	...
}

...

delete pVKDTWindow;
```

<br>

### Other Functions
There may be other functions of use that are needed in VKDT

#### Get Window Size

```cpp
const vkdt::window::size getSize(void) const noexcept;
```

- Get VKDT Window Size.
- The function returns a struct that contains the width and height.
- If you need the size in single variables, you can use the following code.
```cpp
auto [width, height] = pVKDTWindow -> getSize();
```

<br>

#### Get Key State

```cpp
bool isPressed(const vkdt::window::key key) const;
```

- Check if a certain key is pressed.
- There is 1 parameter:
	1. `key` A enumeration of the VKDT key options. You can select it with the following code:
	```cpp
	if(pVKDTWindow -> isPressed(vkdt::window::key::ZERO))
	{
		std::cout << "ZERO Key Pressed!\n";
	}
	```