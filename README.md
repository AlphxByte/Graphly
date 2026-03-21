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
The main project of Graphly, where you will find the entry point of the application and `main.cpp` 
file along with the application logic.

> The App class right now doesn't contain the application logic yet, only
initializing core components of the application.

2. **GraphlyCore**
A static library containing the shared components across multiple projects.

3. **GraphlyDB**
> No description provided for **GraphlyDB** yet as this project is empty. 
This project is intended for providing future database support for the application.

4. **GraphlyMath**
A thin wrapper over DirectXMath library that provides basic math features. 

5. **GraphlyUI** 
Provides a UI system and a UI renderer and predefined controls for the application.

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