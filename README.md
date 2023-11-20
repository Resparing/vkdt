# VKDT
A Vulkan Abstraction to Help Developers
<br>

### Introduction

VKDT is a small & extensible C++ library to help speed up the development process of Vulkan, it has a Singleton/OOP approach, with classes and a global objects file for editing & extending the classes inside VKDT

<br>

### Installation

1. Download the entire project.
2. Setup Makefile
    1. Configure the `INC_DIR`, `INC_LIB`, `INC_DYLIB`, and `INC_FLAGS`
    2. If needed, change the compiler from `clang++` to one of your choice
3. Run Makefile
    - Type `make` into the terminal to build the sample project
    - Type `make debug` into the terminal to build the sample project with debugging

<br>


### Documentation
### Extending VKDT

Each class will have two booleans called `debug` and `verbose`. These are for making sure that your code will be able to debug important information and conform with what the validation layers expect you to setup.
There will be a Vulkan Object to edit in the class as well. If needed, you can access other Vulkan Objects using the `vkdt/_pObjects.h` header. These will contain pointers to all Vulkan Objects for you edit.

### TODO