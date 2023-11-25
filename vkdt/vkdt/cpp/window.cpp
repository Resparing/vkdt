//Include Header File
#include <vkdt/window.h>

//Include Headers
#include <_vkdt/pObjects.h>

vkdt::window::window::window
(
	const vkdt::window::windowArguments windowArgs,
	const bool debug,
	const bool verbose
) : debug(debug), verbose(verbose)
{
	//Set GLFW Window Pointer
	_vkdt::pObjects::pGLFWWindow = &this -> vkdtGLFWWindow;

	//Try to Initialize GLFW
	if(!glfwInit())
	{
		throw std::runtime_error("Failed to Initialize VKDT Window Manager!\n");
	}
	else
	{
		if(this -> verbose)
		{
			std::cout << "Setup Initialization of VKDT Window!\n";
		}
	}

	//Required Window Hint for Vulkan - Setup With no OpenGL Context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	//Set Window Attributes
	for(const auto&[hint, option] : windowArgs)
	{
		//Convert VKDT Attribute & Result to Int for GLFW Window Hint
		std::int32_t vkdtHint = static_cast<int32_t>(hint);
		std::int32_t vkdtOption = static_cast<int32_t>(option);

		//Set Window Hint in GLFW
		glfwWindowHint(vkdtHint, vkdtOption);

		if(this -> verbose)
		{
			//If Verbose Hints are Enabled
			switch(hint)
			{
			case vkdt::window::argument::CENTER_CURSOR:
				std::cout << "Edited Center Cursor VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::DECORATED:
				std::cout << "Edited Decorated VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::DOUBLE_FRAME_BUFFER:
				std::cout << "Edited Double Frame Buffer VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::FLOATING:
				std::cout << "Edited Floating VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::FOCUSED:
				std::cout << "Edited Focused VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::ICON:
				std::cout << "Edited Iconify VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::INIT_WITH_FOCUS:
				std::cout << "Edited Initialize With Focus VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::INIT_WITH_VISIBILITY:
				std::cout << "Edited Initialize Visibility VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::MAXIMIZED:
				std::cout << "Edited Maximized VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::RESIZABLE:
				std::cout << "Edited Resizable VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::SCALE_WITH_MONITOR:
				std::cout << "Edited Scale With Monitor VKDT Window Argument!\n";
				break;
			case vkdt::window::argument::TRANSPARENT_FRAME_BUFFER:
				std::cout << "Edited Transparent VKDT Window Argument!\n";
				break;
			}
		}
	}

	//Check if GLFW Supports Vulkan
	if(glfwVulkanSupported() == GLFW_TRUE)
	{
		if(this -> verbose)
		{
			std::cout << "GLFW Supports Vulkan!\n";
		}
	}
	else
	{
		throw std::runtime_error("Vulkan not Supported with GLFW!\n");
	}

	if(this -> debug || this -> verbose)
	{
		//Debug VKDT Window Initialization Success
		std::cout << "Successfully Initialized VKDT Window!\n";
	}
}

vkdt::window::window::~window()
{
	//Destroy GLFW Window
	glfwDestroyWindow(this -> vkdtGLFWWindow);

	//Terminate GLFW
	glfwTerminate();

	if(this -> verbose)
	{
		std::cout << "Successfully Destroyed VKDT Window and Deallocated all Related Resources!\n";
	}
	else if(this -> debug)
	{
		std::cout << "Successfully Destroyed VKDT Window!\n";
	}
}

void vkdt::window::window::createWindow(const vkdt::window::size& windowSize, const std::string& title)
{
	//Window was Already Created
	if(this -> windowCreated)
	{
		if(this -> verbose)
		{
			//Debug Error
			std::cerr << "Already Created VKDT Window!\n";
		}

		return;
	}

	//Set Window Sizes Using Structured Bindings
	const int windowWidth = static_cast<int>(windowSize.width);
	const int windowHeight = static_cast<int>(windowSize.height);

	//Try to Create GLFW Window
	if((this -> vkdtGLFWWindow = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), nullptr, nullptr)))
	{
		//Debug Window Creation Success
		if(this -> verbose)
		{
			std::cout										\
			<< "Successfully Created VKDT Window With"		\
			<< " Width: " << windowWidth					\
			<< ", Height: " << windowHeight					\
			<< ". Title: \"" << title << "\"!\n";
		}

		else if(this -> debug)
		{
			std::cout << "Successfully Created VKDT Window!\n";
		}
	}
	else
	{
		//Window Creation Failed
		throw std::runtime_error("Failed to Create VKDT Window!\n");
	}

	//Set Window Created to Prevent Recreation of Window
	this -> windowCreated = true;
}

const vkdt::window::size vkdt::window::window::getSize(void) const noexcept
{
	//Temporary Variables to Store Width & Height
	int windowWidth{};
	int windowHeight{};

	glfwGetWindowSize(this -> vkdtGLFWWindow, &windowWidth, &windowHeight);

	//Create Instance of VKDT Window Size Struct
	const vkdt::window::size windowSize =
	{
		.width = static_cast<size_t>(windowWidth),
		.height = static_cast<size_t>(windowHeight),
	};

	return windowSize;
}

bool vkdt::window::window::isOpen(void) const noexcept
{
	//Return Opposite of GLFW Window Should Close
	return !glfwWindowShouldClose(this -> vkdtGLFWWindow);
}

void vkdt::window::window::update(void) const noexcept
{
	//Call GLFW Poll Events Function
	glfwPollEvents();
}

bool vkdt::window::window::isPressed(const vkdt::window::key key) const
{
	//Convert Key to Integer
	const int intKey = static_cast<int>(key);

	//Get State of Requested Key
	const std::uint8_t keyState = static_cast<std::uint8_t>(glfwGetKey(this -> vkdtGLFWWindow, intKey));

	//Check if State is "Pressed State"
	if(keyState == GLFW_PRESS)
	{
		return true;
	}
	else if(keyState == GLFW_RELEASE)
	{
		return false;
	}

	//No Key State was Found
	throw std::runtime_error("Failed to Find Key State!\n");
}