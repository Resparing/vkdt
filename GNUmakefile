#App Name and Directory
APP_NAME := VulkanDevTools
APP_DIR := bin/

#Application Path
APP_PATH := $(APP_DIR)$(APP_NAME)

#C++ Files
CPP_FILES := $(wildcard src/cpp/*.cpp) $(wildcard src/hpp/cpp/*.cpp) $(wildcard lib/inc/*.cpp) $(wildcard vkdt/cpp/*.cpp)

#C++ Information
CPP_INFO := -std=c++20 -O0

#C++ Compiler
CPP_COMPILER := clang++

#C++ Warnings
CPP_WARNING := -Wall -Wextra -Wpedantic -Wstrict-aliasing -Wconversion -Wshadow -Wdeprecated #-Werror

#Includes
INC_DIR := 		"-I/Users/hudsonregis/Desktop/Projects/Vulkan Projects/VKDT/lib/hpp"			\
				"-I/Users/hudsonregis/Desktop/Projects/Vulkan Projects/VKDT/"					\
				"-I/Users/hudsonregis/VulkanSDK/1.3.268.1/macOS/include"
INC_LIB :=		"-L/Users/hudsonregis/Desktop/Projects/Vulkan Projects/VKDT/lib/inc"			\
				"-L/Users/hudsonregis/VulkanSDK/1.3.268.1/macOS/lib"
INC_DYLIB :=	-Wl,-rpath, "/Users/hudsonregis/Desktop/Projects/Vulkan Projects/VKDT/lib/inc"	\
				-Wl,-rpath, "/Users/hudsonregis/VulkanSDK/1.3.268.1/macOS/lib"
INC_FLAGS := -lglfw.3 -lvulkan

#Massive Include
INC := $(INC_DIR) $(INC_LIB) $(INC_DYLIB) $(INC_FLAGS)

#MacOS Frameworks
FRAMEWORKS :=# -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreGraphics

.PHONY: build debug compile clear

#Build Command
build:
	make compile
	make open
	make clear

#Debug Command
debug:
	make compile
	./$(APP_PATH) DEBUG
	make clear

#Compile Command
compile:
	$(CPP_COMPILER) $(CPP_INFO) -v -o $(APP_PATH) $(CPP_FILES) $(INC) $(CPP_WARNING) $(FRAMEWORKS)

#Open Command
open:
	./$(APP_PATH)

#Clear Terminal Command
clear:
	rm -rf $(APP_PATH)