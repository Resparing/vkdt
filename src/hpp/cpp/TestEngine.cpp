//Include Header File
#include "../TestEngine.hpp"

//Include Headers

//Callback Function
void callback
(
	const VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	const VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* messageData
)
{
	if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
	{
		if(messageType >= VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
		{
			std::cerr											\
			<< "[DEBUG " << messageData -> pMessageIdName		\
			<< ": " << messageData -> messageIdNumber			\
			<< "] " << messageData -> pMessage << "\n\n";
		}
	}
}

TestEngine::TestEngine::TestEngine(const bool debug, const bool verbose) : isDebug(debug), isVerbose(verbose)
{
	//Create Window
	this -> createWindow();

	//Initialize VKDT
	this -> vkdtInit();

	//Run Main Loop
	this -> mainLoop();
}

void TestEngine::TestEngine::createWindow(void)
{
	//Set Arguments for Vulkan Window
	const vkdt::window::windowArguments windowArgs =
	{
		{vkdt::window::argument::RESIZABLE, vkdt::window::result::FALSE},
	};

	//Allocate VKDT Window
	this -> vkdtWindow = new vkdt::window::window(windowArgs, isDebug, isVerbose);

	//Create VKDT Window
	this -> vkdtWindow -> createWindow({1280, 720}, "Test Engine");
}

void TestEngine::TestEngine::vkdtInit(void)
{
	vkdt::instance::applicationInfo appInfo =
	{
		.name = "Test Engine",

		.version.patch = 1,
		.version.major = 1,
		.version.minor = 3,
		.version.variant = 268,
	};
	this -> vkdtInstance = new vkdt::instance::instance(appInfo, isDebug, isVerbose);
	this -> vkdtInstance -> createVKDTInstance(nullptr);

	this -> vkdtInstance -> makeVKDTDebugMessenger(callback);

	this -> vkdtGPU = new vkdt::GPU::GPU(vkdtInstance, isDebug, isVerbose);
	this -> vkdtGPU -> findVKDTGPU();
}

void TestEngine::TestEngine::mainLoop(void)
{
	while(this -> vkdtWindow -> isOpen())
	{
		this -> vkdtWindow -> update();
	}
}

TestEngine::TestEngine::~TestEngine()
{
	delete this -> vkdtGPU;  //Delete VKDT GPU
	delete this -> vkdtInstance;  //Delete VKDT Instance
	delete this -> vkdtWindow;  //Delete VKDT Window
}