#App Name and Directory
APP_NAME := VulkanDevTools
APP_DIR := bin/

#Application Path
APP_PATH := $(APP_DIR)$(APP_NAME)

#C++ Files
CPP_SRC := $(wildcard src/cpp/*.cpp) $(wildcard src/hpp/cpp/*.cpp) $(wildcard vkdt/vkdt/cpp/*.cpp) $(wildcard vkdt/_vkdt/cpp/*.cpp)

#GLSL Directory
SPIRV_SRC := "src/glsl/"

#C++ Information
CPP_INFO := -std=c++20 -stdlib=libc++ -O0

#C++ Compiler
CPP_COMPILER := clang++

#SPRIR-V Compiler
SPRV_COMPILER := "/Users/hudsonregis/VulkanSDK/1.3.268.1/macOS/bin/glslc"

#C++ Warnings
CPP_WARNING := -Wall -Wextra -Wpedantic -Wstrict-aliasing -Wconversion -Wshadow -Wdeprecated #-Werror

#Includes
INC_DIR := 	 "-Ilib/inc"													\
			 "-Ivkdt/"														\
			 "-I/Users/hudsonregis/VulkanSDK/1.3.268.1/macOS/include"
INC_LIB :=	 "-Llib/res/glfw"												\
			 "-Llib/res/vulkan"
INC_DYLIB := -Wl,-rpath,"@executable_path/../lib/res/glfw"					\
			 -Wl,-rpath,"@executable_path/../lib/res/vulkan"
INC_FLAGS := -lglfw.3 -lvulkan.1

#Massive Include
INC := $(INC_DIR) $(INC_LIB) $(INC_DYLIB) $(INC_FLAGS)

#MacOS Frameworks
FRAMEWORKS :=# -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreGraphics

.PHONY: build debug compile shader clear

#Build Project Command
build:
	@make shader
	@make compile
	@make open
	@make clear

#Create & Debug Project Command
debug:
	@make shader
	@make compile
	@./$(APP_PATH) DEBUG
	@make clear

#Compile Project Command
compile:
	$(CPP_COMPILER) $(CPP_INFO) -v -o $(APP_PATH) $(CPP_SRC) $(INC) $(CPP_WARNING) $(FRAMEWORKS)

#Open Executable Command
open:
	./$(APP_PATH)

#Clear Terminal Command
clear:
	rm -rf $(APP_PATH)
	rm -rf $(APP_DIR)vert.spv
	rm -rf $(APP_DIR)frag.spv

#Compile Shaders
shader:
	$(SPRV_COMPILER) $(SPIRV_SRC)shader.vert -o $(APP_DIR)vert.spv
	$(SPRV_COMPILER) $(SPIRV_SRC)shader.frag -o $(APP_DIR)frag.spv