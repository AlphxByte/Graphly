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
1. Win32 (used mainly for creating the application window).
2. DirectXMath.
3. Direct2D and Direct3D 11 (rendering ui elements).
4. DXGI.

> [!NOTE]
> The project doesn't link DirectX libraries in the linker options yet, and those
libraries will be linked and used by the project in the next release.

## Project Structure
1. **Graphly** 
the main project of **Graphly**, where you will find the entry point of the application 
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
│	 │	 └── Logger (raw pointer to Logger from App)
│	 ├── Logger
│	 └── MemoryTracker
└── SystemMetrics
```

### App component
**App** is the main component for the **Graphly** project that will initialize
the application and created the subcomponents from the diagram above.
> [!NOTE]
> **App** component is only initializing the subcomponents and doesn't provide
the application logic yet.<br>

### App settings
```cpp
struct AppSettings final
{
	HINSTANCE instance{};
	int nCmdShow{};
	std::optional<std::string> logFilePath{};
};
```

- **instance** is the handle to the currrent instance of the application.
- **nCmdShow** is the show flag given by the main function to tell the window how to 
show the window on screen.
- **logFilePath** a path to where the log file of the app should be created.
> [!NOTE]
> If no path is given then the path is: `CurrentDir\GraphlyLogs.txt`.

### App functions
**WindowProcedure** function:
```cpp
static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
```
This function is used to handle window events, where:
- **hwnd** is the handle of the window.
- **message** is the message sent by the event loop.
- **wParam** and **lParam** contain additional information about the message sent.

**AlreadyRunning** function:
```cpp
static bool AlreadyRunning();
```
Used for checking if the app is already opened. Returns true if it is already opened or false
otherwise.

**Run** function:
```cpp
[[nodiscard]] int Run();
```
This function is used to run the application and returns the exit code of the app. 
> [!NOTE]
> The Run function is used right now only to run the window of the application.

### GraphlyWindow component
**GraphlyWindow** is a child class of the **Window** class from the **GraphlyUI** project
that will handle the application specific logic for the main window.
> [!NOTE]
> **GraphlyWindow** component might be changed in the future to **GraphlyMainWindow**.<br>

### Logger component
**Logger** component is used for writing messages inside a log file or writing 
a message using a popup window. This component has 3 message types: Information, Warning and Error. 
If the **Logger** component doesn't get a file path to a log file to create it; it 
will be created based on the **ProjectDir** environment variable.<br>

### Logger settings
```cpp
using LogPath = std::optional<std::string>;

struct LoggerSettings final
{
	LogPath logPath;
};
```
- **logPath** is the file path given from the **App** component.

### Logger functions
**WriteLogMessage** functions:
```cpp
void WriteLogMessage(const Message& msg);
void WriteLogMessage(Message&& msg);
```
Used to write log messages to the app log file. Where **Message** type is:

```cpp
enum class MessageType
{
	Information = 0,
	Warning,
	Error
};

struct Message final
{
	MessageType type{};
	std::string str{};
};
```

- **type** is the type of the message.
- **str** the string of message.

**WritePopupMessage** functions:
```cpp
void WritePopupMessage(const Message& msg);
void WritePopupMessage(Message&& msg);
```
Used to write popup message.
> [!TIP]
> Use this function when the message is important to the user and use **WriteLogMessage** function
> for more detailed messages.

### MemoryTracker component
**MemoryTracker** for detecting memory leaks and unreleased resources for the **App** component.
This component is only used in **DEBUG** mode.
> [!IMPORTANT]
> An issue was found where if an error was thrown by the **App** class 
> it will show in the output window as a memory leak. This is because std::runtime_error 
> allocates a string that was given, and that string lasts longer than the **App** class 
> because it needs to beused in the catch block inside `Graphly\src\main.cpp`. 
> After the catch block ends, the string is deallocated.<br>

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
	│       └── UIFactory (raw pointer to UIFactory from UIContext)
	├── WindowFlags
	└── WindowSettings
```

### Window component
**Window** component is a general window class that provides basic window
functionality for a window.<br>

### Window Functions
**Run** function:
```cpp
[[nodiscard]] int Run();
```
This function is used to run the event loop for the window.

### UIContext component
**UIContext** is a subcomponent of the **Window** class that holds all the
resources of the ui system including the rendering resources and the ui tree of controls.
This component is also responsible for the creation of the root ui element that has the rect 
size of the window where all the ui elements will be placed. 
Every node from the ui element has the following structure:<br>

```txt
UIElement
├── UIFactory (raw pointer to the UIFactory from UIContext)
├── Parent
└── Children 
```

- **Parent** is a node from the ui tree of type UIElement that holds a pointer 
to the parent of the current ui element. If the current node is the root of 
the tree then this pointer is null.<br>

- **Children** is a **std::unordered_map** that holds as the key the name of a child
ui element and the pointer to that element.<br>

### UIElement
**UIElement** is a abstract class that represents a generic ui element on a window.
**GraphlyUI** also provides predefined ui elements such as: TextField, Button and Image.
When a ui element object derived from UIElement is created the assigned type to the 
element is **TextField** (ui element with only text and no other functionality).
**UIElement** class has the following fields that you can set:<br>
> [!NOTE]
> A object of type UIElement cannot be copied.

```cpp
struct GRAPHLYUI_API UIElementSettings
{
	UIElement* parent{};
	std::wstring text{};
	GraphlyMath::Vector2 position{ 0, 0 };
	GraphlyMath::Vector2 dimension{ 50, 50 };

protected:
	UIElementType type = UIElementType::TextField;

	UIElementSettings(UIElementType type = UIElementType::TextField)
	: type(type) {}

	friend class UIElement;
};
```

- **parent** a pointer to the parent element.
- **text** a wide string that contains the text of the ui element.
- **position** position on the window.
- **dimension** dimension of the ui element.

### UIElement functions
**AddUIElement** functions:
```cpp
UIElement* AddUIElement(std::string_view name, const UIElementSettings& settings);
UIElement* AddUIElement(std::string_view name, UIElementSettings&& settings);
```
Used to add a child element to the current ui element, where:
- **name** is used for the unique name to identify the ui element.
- **settings** settings for the ui element (see **UIElementSettings**).

This function returns a pointer to the added element if it was added otherwise nullptr if 
the function failed to add the element.

**DeleteUIElement** functions:
```cpp
bool DeleteUIElement(std::string_view name); (1)
bool DeleteUIElement(UIElement* parent, std::string_view elementName); (2)
```
1. Used to delete a child ui element from the subtree where the root of the subtree is
the current ui element. This function deletes recursively the subtree of the child element. 
The return value of this function is true if the element was deleted or false otherwise.
2. Same thing as the (1) function but allows for a faster deletion by providing the parent
of the element. 
> [!TIP]
> Use function signature (2) to reduce searches of the child element in the subtree.

**GetUIElement** functions:
```cpp
[[nodiscard]] UIElement* GetUIElement(std::string_view name); (1)
[[nodiscard]] UIElement* GetUIElement(UIElement* parent, std::string_view elementName); (2)
```
1. Used to search the subtree of the current ui element for the child element with the 
name provided and returns a raw pointer if element is found otherwise it returns nullptr. 
2. Same thing as (1) but allows for a faster search by providing the parent of the element.
> [!TIP]
> Use function signature (2) to reduce searches of the child element in the subtree.

### WindowSettings
**WindowSettings** is a component that is used to initialize the **Window**
component and handle the lifetime of the window resources such as win32 handles
to icons, cursor and other **gdi+** resources. See 
`GraphlyUI\include\GraphlyUI\Window\WindowSettings.h` to see what settings 
can be set for a window.

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