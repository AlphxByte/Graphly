# Graphly
## Description
This is a C++ project made for the POO course from **University of Bucharest**.

**Graphly** is a Windows-based application that lets you design
graph-based diagrams for your project architecture, 
allowing you to visualize structure and relationships between
different components of your system or application. 

> This is project is still in development. 

## Dependencies
1. Win32 (used mainly for creating the application window)
2. DirectXMath 
3. Direct2D and Direct3D 11 (rendering ui elements)
4. DXGI

> The project doesn't link DirectX libraries in the linker options yet, and those
libraries will be linked and used by the project in the next release.

## Project Structure
1. **Graphly** 
the main project of Graphly, where you will find the entry point of the application and `main.cpp` 
file along with the application logic.

> The App class right now doesn't contain the application logic yet, only
initializing core components of the application.

2. **GraphlyDB**
> No description provided for **GraphlyDB** yet as this project is empty. 
This project is intended for providing future database support for the application.

3. **GraphlyMath**
a thin wrapper over DirectXMath library that provides basic math features. 

4. **GraphlyUI** 
Provides a UI system and a UI renderer and predefined controls for the application.

## How it works

### Application logic
The application logic is handled by the App and GraphlyWindow classes. 
The App class has 3 main components:

1. **MemoryTracker** for detecting memory leaks and unreleased resources.
> An issue was found where if an error was thrown by the **App*** class it will show in 
the output window inside as a memory leak. This is because std::runtime_error allocates 
a string that was given and that string lasts longer than the **App** class because it needs to be
used in the catch block inside `main.cpp`. After the catch block ends, the string is deallocated.

2. **Logger** component is used for writing messages inside a log file or writing a message using a popup window.
This component has 3 message types: Information, Warning and Error. If the Logger component 
doesn't get a file path to a log file to create it; it will be created based on the CurrentDir
environment variable.

3. **GraphlyWindow** a subclass of **Window** class from the **GraphlyUI** project.
> This class is currently empty and doesn't have logic yet.

### Math library
**GraphlyMath** project is a dll that is used across the project for math-related calculations.
Features provided by **GraphlyMath**:<br>

1. **FloatN** is an array of floats used mainly for storing float values together.
2. **FloatNxM** a matrix of floats.
3. **Vector** is a SIMD-optimized version of **FloatN** used to store float values up to 4 
floats inside a **Vector** object.
4. **Matrix4x4** is a SIMD-optimized matrix with 4x4 dimensions. Every line of the matrix
is of type **Vector**.

### UI System
1. **GraphlyUI** project is a dll that is used by the App component to initialize the UI System
of the **GraphlyWindow**. Below is a description of the entire UI System.<br>

- Window
	- UIContext
		- UIFactory
		- UIElement (root of the ui tree)
		- UIRenderer 

- **UIContext** component is the root component for all the UI subcomponents.
- **UIFactory** component is used for creating generic **UIElement** objects.
- **UIRenderer** 
> This component is work in progress.

**GraphlyUI** also provides predefined ui elements of type: TextField, Button, Image.
> Those ui elements don't have an implementation yet.

2. **UIElement** is an abstract class that provides a base for ui elements. Every ui element
holds a collection of child ui elements and every ui element holds a pointer to its parent
(root element has the parent pointer set to null).

## Setup
1. Visual Studio 2022
2. C++ Desktop Development

## How to Build
1. Open `Graphly.sln` in Visual Studio.
2. Select Debug or Release.
3. Build Solution.

## How to Run
1. Select **Graphly** as Startup Project.
2. Press Run or F5.