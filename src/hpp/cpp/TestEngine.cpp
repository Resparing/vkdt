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

		for(size_t i{}; i < messageData -> queueLabelCount; ++i)
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

		for(size_t i{}; i < messageData -> cmdBufLabelCount; ++i)
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
	this -> vkdtDebugMessenger = new vkdt::debug::messenger(callback, isDebug, isVerbose);

	vkdt::instance::envVariables envData =
	{
		.VK_ICD_FILENAMES = "lib/inc/vulkan/icd.d/MoltenVK_icd.json",
		.VK_LAYER_PATH = "lib/inc/vulkan/explicit_layer.d",
	};
	vkdt::instance::applicationData appInfo =
	{
		.name = "Test Engine",

		.version.patch = 1,
		.version.major = 1,
		.version.minor = 3,
		.version.variant = 268,
	};
	this -> vkdtInstance = new vkdt::instance::instance(envData, appInfo, isDebug, isVerbose);
	this -> vkdtInstance -> setupVKDTInstance({}, {});
	this -> vkdtInstance -> createVKDTInstance(nullptr);

	this -> vkdtDebugMessenger -> createVKDTDebugMessenger(nullptr);

	this -> vkdtSurface = new vkdt::surface::surface(isDebug, isVerbose);
	this -> vkdtSurface -> createVKDTSurface(nullptr);

	this -> vkdtGraphicsQueue = new vkdt::queue::queue(isDebug, isVerbose);

	this -> vkdtGPU = new vkdt::GPU::GPU(isDebug, isVerbose);
	this -> vkdtGPU -> findVKDTGPU(nullptr);

	this -> vkdtDevice = new vkdt::device::device({}, {}, isDebug, isVerbose);
	this -> vkdtDevice -> createVKDTDevice(nullptr);
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
	delete this -> vkdtDevice;  //Delete VKDT Device
	delete this -> vkdtDebugMessenger;  //Delete VKDT Debug Messenger
	delete this -> vkdtSurface;  //Delete VKDT Surface
	delete this -> vkdtInstance;  //Delete VKDT Instance
	delete this -> vkdtWindow;  //Delete VKDT Window

	delete this -> vkdtGraphicsQueue;  //Delete VKDT Graphics Queue
	delete this -> vkdtGPU;  //Free Memory
}