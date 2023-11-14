//Include Header File
#include "../TestEngine.hpp"

//Include Headers

//Callback Function
static void callback
(
	const VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	const VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* messageData
)
{
	if(messageSeverity < VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT || messageType < VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
	{
		return;
	}

	//Debug Message Information
	std::cerr																			\
	<< "[DEBUG " << messageData -> pMessageIdName										\
	<< ": " << messageData -> messageIdNumber											\
	<< "] " << messageData -> pMessage << "\n";

	//Check if Queue Labels Exist
	if(messageData -> queueLabelCount > 0 && messageData -> pQueueLabels)
	{
		//Debug Queue Labels
		std::cerr << "Message Labels (" << messageData -> queueLabelCount << "):\n";

		for(std::size_t i{}; i < messageData -> queueLabelCount; ++i)
		{
			std::cerr << "\t[" << i << "][QUEUE MESSAGE] \"" << messageData -> pQueueLabels[i].pLabelName << "\"\n";
		}
	}

//	//Check if Objects Exist
//	if(messageData -> objectCount > 0 && messageData -> pObjects)
//	{
//		//Debug Message Labels
//		std::cerr << "Objects (" << messageData -> objectCount << "):\n";
//
//		for(std::size_t i{}; i < messageData -> objectCount; ++i)
//		{
//			std::cerr																	\
//			<< "\t[" << i << "][OBJECT: " << messageData -> pObjects[i].objectType		\
//			<< "] Name: \"" << messageData -> pObjects[i].pObjectName << "\""			\
//			<< " Location: " << (void*)(messageData -> pObjects[i].objectHandle) << "\n";
//		}
//	}

	//Check if Command Buffers Exist
	if(messageData -> cmdBufLabelCount > 0 && messageData -> pCmdBufLabels)
	{
		//Debug Command Buffer Labels
		std::cerr << "Command Buffer Labels (" << messageData -> cmdBufLabelCount << "):\n";

		for(std::size_t i{}; i < messageData -> cmdBufLabelCount; ++i)
		{
			std::cerr << "\t[" << i << "][COMMAND BUFFER] \"" << messageData -> pCmdBufLabels[i].pLabelName << "\"\n";
		}
	}

	//Print Extra Newline Character
	std::cerr << '\n';
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
	const vkdt::window::windowArguments windowArgs = {{vkdt::window::argument::RESIZABLE, vkdt::window::result::FALSE}};

	//Initialize VKDT Window
	this -> vkdtWindow = new vkdt::window::window(windowArgs, isDebug, isVerbose);

	//Create VKDT Window
	this -> vkdtWindow -> createWindow({1280, 720}, "Test Engine");
}

void TestEngine::TestEngine::vkdtInit(void)
{
	vkdt::instance::applicationData appInfo =
	{
		.name = "Test Engine",

		.version.patch = 1,
		.version.major = 1,
		.version.minor = 3,
		.version.variant = 268,
	};
	this -> vkdtInstance = new vkdt::instance::instance(appInfo, {}, {}, isDebug, isVerbose);
	this -> vkdtInstance -> createVKDTInstance(callback, nullptr);

	this -> vkdtInstance -> makeVKDTDebugMessenger();

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