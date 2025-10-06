# Welcome!

SDE is a development tool for C++ which will soon be cross-platform


## Current Stack

I'm currently using CMake with a custom bash script to build the program.


For rendering I use GLFW (OpenGL) with ImGui so that it works cross-platform and also doesn't require a completely new stack when I want to port this to Windows or macOS.


The Text Editor itself I will create my own (with `ImGuiColorTextEdit` as a base) and the LSP for it will have to be decided.


Any compiler should be able to be used (GCC, Clang, and even MSVC for Windows) for my IDE as I'm looking for the best options possible.
However I'm looking towards a custom build system that will compile itself into a CMake Script.