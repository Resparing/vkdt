//Header Guard
#pragma once

//Include Headers
#include <_vkdt/vkdtConfig.h>
#include <_vkdt/windowEnum.h>

namespace vkdt::window
{
	//Typedef for VKDT Window Arguments
	typedef std::unordered_map<vkdt::window::argument, vkdt::window::result> windowArguments;

	//Window Class
	class window
	{
	public:
		/**
		 * @brief Setup VKDT Window With Specified Arguments
		 *
		 * @param windowArgs VKDT Window Arguments Window will Posses
		 * @param debug Whether to Allow Debugging in Messages
		 * @param verbose Allow General & Verbose Debugging Methods in Messages
		 */
		window(const windowArguments windowArgs = {}, const bool debug = false, const bool verbose = false);

		~window();

		/**
		 * @brief Create a Window
		 *
		 * @param size The size of the Window
		 * @param TITLE The Title of the Window
		 */
		void createWindow(const vkdt::window::size& windowSize = {800, 600}, const std::string& title = "");

		/**
		 * @brief Get the Window Size
		 *
		 * @return Struct Containing Width & Height of VKDT Window
		 */
		const vkdt::window::size getSize(void) const noexcept;

		/**
		 * @brief Check if Window Should Stay Open
		 *
		 * @return true if Window Should Stay Open, false if should close
		 */
		bool isOpen(void) const noexcept;

		/**
		 * @brief Update VKDT Window
		 */
		void update(void) const noexcept;

		/**
		 * @brief Check if Specified Key was Pressed
		 *
		 * @param key Key to Check if Pressed
		 *
		 * @return true if key is pressed, false if not pressed
		 */
		bool isPressed(const vkdt::window::key key) const;

	private:

		//If Window Created
		bool windowCreated{};

	protected:

		//GLFW Window
		GLFWwindow* vkdtGLFWWindow;

		//Debugging Variables
		bool debug{};
		bool verbose{};

	};
}