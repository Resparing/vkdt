//Include Header File
#include "../TestEngine.hpp"

//Callback Function
static void callback
(
	const vkdt::debug::messageSeverity messageSeverity,
	const vkdt::debug::messageType messageType,
	const vkdt::debug::messageData messageData
)
{
	if(messageSeverity < vkdt::debug::messageSeverity::VERBOSE || messageType < vkdt::debug::messageType::VERBOSE)
	{
		return;
	}

	//Debug Message Information
	std::cerr << "\n[DEBUG " << messageData.messageIDName << ": " << messageData.messageID << "] " << messageData.message << "\n";

	//Check if Queue Labels Exist
	if(!messageData.queueLabels.empty())
	{
		//Debug Queue Labels
		std::cerr << "Message Labels (" << messageData.queueLabels.size() << "):\n";

		for(const vkdt::debug::label& queueLabel : messageData.queueLabels)
		{
			std::cerr << "\t[QUEUE LABEL] Name: \"" << queueLabel.labelName << "\"\n";
		}
	}

	//Check if Objects Exist
	if(!messageData.objects.empty())
	{
		//Debug Message Labels
		std::cerr << "Objects (" << messageData.objects.size() << "):\n";

		for(const vkdt::debug::object& object : messageData.objects)
		{
			std::cerr
			<< "\t[OBJECT] ID: " << object.objectType
			<< " Name: \"" << object.objectName
			<< "\" Handle: " << (void*)object.objectHandle << "!\n";
		}
	}

	//Check if Command Buffers Exist
	if(!messageData.commandBuffers.empty())
	{
		//Debug Command Buffer Labels
		std::cerr << "Command Buffer Labels (" << messageData.commandBuffers.size() << "):\n";

		for(const vkdt::debug::label& commandBuffer : messageData.commandBuffers)
		{
			std::cerr << "\t[COMMAND BUFFER] \"" << commandBuffer.labelName << "\"!\n";
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

	vkdt::instance::applicationData appInfo =
	{
		.name = "Test Engine",

		.version =
		{
			.patch = 1,
			.major = 1,
			.minor = 3,
			.variant = 268,
		},
	};
	this -> vkdtInstance = new vkdt::instance::instance(appInfo, isDebug, isVerbose);
	this -> vkdtInstance -> setupVKDTInstance({}, {});
	this -> vkdtInstance -> createVKDTInstance(nullptr);

	this -> vkdtDebugMessenger -> createVKDTDebugMessenger(nullptr);

	this -> vkdtSurface = new vkdt::surface::surface(isDebug, isVerbose);
	this -> vkdtSurface -> createVKDTSurface(nullptr);

	this -> vkdtQueue = new vkdt::queue::queue(isDebug, isVerbose);

	this -> vkdtGPU = new vkdt::GPU::GPU(isDebug, isVerbose);
	this -> vkdtGPU -> findVKDTGPU(nullptr);

	this -> vkdtDevice = new vkdt::device::device({}, {}, isDebug, isVerbose);
	this -> vkdtDevice -> createVKDTDevice(nullptr);

	this -> vkdtImageView = new vkdt::imageView::imageView(isDebug, isVerbose);

	this -> vkdtSwapchain = new vkdt::swapchain::swapchain(isDebug, isVerbose);
	this -> vkdtSwapchain -> createVKDTSwapchain(nullptr);

	this -> vkdtImageView -> createImageView(nullptr);

	this -> vkdtPipeline = new vkdt::pipeline::pipeline(isDebug, isVerbose);
	this -> vkdtPipeline -> createVKDTPipeline("bin/vert.spv", "bin/frag.spv", nullptr);
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
	delete this -> vkdtPipeline;  //Delete VKDT Pipeline
	delete this -> vkdtImageView;  //Delete VKDT Image View
	delete this -> vkdtSwapchain;  //Delete VKDT Swapchain
	delete this -> vkdtDevice;  //Delete VKDT Device
	delete this -> vkdtDebugMessenger;  //Delete VKDT Debug Messenger
	delete this -> vkdtSurface;  //Delete VKDT Surface
	delete this -> vkdtInstance;  //Delete VKDT Instance
	delete this -> vkdtWindow;  //Delete VKDT Window

	delete this -> vkdtQueue;  //Delete VKDT Queue
	delete this -> vkdtGPU;  //Free Memory
}