# Graphly
## Description
This is a C++ project made for the POO course from **University of Bucharest**.

**Graphly** is a Windows-based application that lets you design
graph-based diagrams for your project architecture, 
allowing you to visualize structure and relationships between
different components of your system or application. 

> [!NOTE]
> This is project is still in development. 

## Dependencies
1. Win32 (used mainly for creating the application window)
2. DirectXMath 
3. Direct2D and Direct3D 11 (rendering ui elements)
4. DXGI

> [!NOTE]
> The project doesn't link DirectX libraries in the linker options yet, and those
libraries will be linked and used by the project in the next release.

## Project Structure
1. **Graphly** 
the main project of Graphly, where you will find the entry point of the application 
and `main.cpp` file inside `Graphly\src` folder along with the application logic.

> [!NOTE]
> The App class right now doesn't contain the application logic yet, only
initializing core components of the application.

2. **GraphlyDB**
> [!NOTE]
> No description provided for **GraphlyDB** yet as this project is empty. 
This project is intended for providing future database support for the application.

3. **GraphlyMath**
a thin wrapper over DirectXMath library that provides basic math features. 

4. **GraphlyUI** 
Provides a UI system and a UI renderer and predefined controls for the application.

## How it works

### Application logic
The application logic is handled by the App and GraphlyWindow classes. 
Below there is a diagram showing the structure of **Graphly** project:<br>

```txt
Graphly (namespace)
├── App
│	 ├── GraphlyWindow
│	 ├── Logger
│	 └── MemoryTracker
└── SystemMetrics
```

1. **App** is the main component for the **Graphly** project that will initialize
the application and created the subcomponents from the diagram above.
> [!NOTE]
> **App** component is only initializing the subcomponents and doesn't provide
the application logic yet.<br>

#### App functions

```cpp
static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
```
This function is used to handle window events, where:
- **hwnd** is the handle of the window.
- **message** is the message sent by the event loop.
- **wParam** and **lParam** contain additional information about the message sent.

```cpp
static bool AlreadyRunning();
```
Used for checking if the app is already opened. Returns true if it is already opened and false
otherwise.

```cpp
[[nodiscard]] int Run();
```
This functions is used to run the application and returns the exit code of the app. 
> [!NOTE]
> The Run function is used right now only to run the window.

2. **GraphlyWindow** is a child class of the **Window** class from the **GraphlyUI** project
that will handle the application specific logic for the main window.
> [!NOTE]
> **GraphlyWindow** component might be changed in the future to **GraphlyMainWindow**.<br>

3. **Logger** component is used for writing messages inside a log file or writing 
a message using a popup window. This component has 3 message types: Information, Warning and Error. 
If the Logger component doesn't get a file path to a log file to create it; it 
will be created based on the CurrentDir environment variable.<br>

#### Logger functions

```cpp
void WriteLogMessage(const Message& msg);
void WriteLogMessage(Message&& msg);
```
Used to write log messages to the app log file.

```cpp
void WritePopupMessage(const Message& msg);
void WritePopupMessage(Message&& msg);
```
Used to write popup message.
> [!TIP]
> Use this function when the message is important to the user and use **WriteLogMessage** function
> for more detailed messages.

4. **MemoryTracker** for detecting memory leaks and unreleased resources for the **App** component.
> [!IMPORTANT]
> An issue was found where if an error was thrown by the **App** class 
it will show in the output window as a memory leak. This is because std::runtime_error 
allocates a string that was given, and that string lasts longer than the **App** class 
because it needs to beused in the catch block inside `Graphly\src\main.cpp`. 
After the catch block ends, the string is deallocated.

### Math library
**GraphlyMath** project is a DLL that is used across the project for math-related calculations.
Features provided by **GraphlyMath**:<br>

1. **FloatN** is an array of floats used mainly for storing float values together.
2. **FloatNxM** a matrix of floats.
3. **Vector** is a SIMD-optimized version of **FloatN** used to store float values up to 4 
floats inside a **Vector** object.
> [!TIP]
> Use **Vector** object for vector optimized calculations with dimensions of 2, 3 or 4
> and use FloatN for general purpose calculations with higher number of dimensions.
4. **Matrix4x4** is a SIMD-optimized matrix with 4x4 dimensions. Every line of the matrix
is of type **Vector**.
> [!TIP]
> Use **Matrix4x4** object for optimized calculations with matrices of 4x4 dimension
> and use FloatNxM for general purpose calculations with matrices.

### UI System
**GraphlyUI** project is a DLL that is used by the **App** component to initialize the UI System
of the **GraphlyWindow**. Below is a description of the entire UI System.
> [!NOTE]
> This system is subject to change and the diagram below will change in a future
update as this system will provide a way to render ui controls on a window.<br>

```txt
GraphlyUI (namespace)
└── Window
	├── UIContext 
	│	├── UIFactory 
	│	├── UIRenderer (not included inside UIContext as a subcomponent yet)
	│	└── UIElement (root of the UI System)
	├── WindowFlags
	└── WindowSettings
```

1. **Window** component is a general window class that provides basic window
functionality for a window.<br>

2. **UIContext** is a subcomponent of the **Window** class that holds all the
resources of the ui system including the rendering resources and the ui tree of controls.
This component is also responsible for the creation of the root ui element that has the rect 
size of the window where all the ui elements will be placed. 
Every node from the ui element has the following structure:<br>

```txt
UIElement
├── UIFactory (raw pointer to the UIFactory component from UIContext)
├── Parent
└── Children 
```

- **Parent** is a node from the ui tree of type UIElement that holds a pointer 
	   to the parent of the current ui element. If the current node is the root of 
	   the tree then this pointer is null.<br>

- **Children** is a **std::unordered_map** that holds as the key the name of a child
	   ui element and the pointer to that element.<br>

3. **UIElement** is a abstract class that represents a generic ui element on a window.
**GraphlyUI** also provides predefined ui elements such as: TextField, Button and Image.
When a generic UIElement object is created the assigned type to the element is TextField 
(ui element with only text and no other functionality).
**UIElement** class has the following fields that you can set:<br>

```cpp
UIElement* parent{};
std::wstring text{};
GraphlyMath::Vector2 position{ 0, 0 };
GraphlyMath::Vector2 dimension{ 50, 50 };
```

4. **WindowSettings** is a component that is used to initialize the **Window**
component and handle the lifetime of the window resources such as win32 handles
to icons, cursor and other **gdi+** resources.

## Setup
1. Visual Studio 2022.
2. C++ Desktop Development.

## How to Build
1. Open `Graphly.sln` in **Visual Studio**.
2. Select **Debug** or **Release**.
3. Build Solution.

## How to Run
1. Select **Graphly** as **Startup Project**.
2. Press **Run** or **F5**.