#include <filesystem>

#include "App.h"

using namespace Graphly;
using namespace GraphlyCore;
using namespace GraphlyUI;
using namespace GraphlyMath;

HANDLE App::_mutex = nullptr;

App::App(const AppSettings& settings)
{
	_settings = settings;
	[[unlikely]] if (!Initialize())
		throw std::runtime_error("App initialization failed.");
}

App::App(AppSettings&& settings)
{
	_settings = std::forward<AppSettings>(settings);
	[[unlikely]] if (!Initialize())
		throw std::runtime_error("App initialization failed.");
}

bool App::Initialize()
{
#ifdef _DEBUG
	_memoryTracker = std::make_unique<MemoryTracker>();
	if (!_memoryTracker)
		return false;

#endif // _DEBUG (MemoryTracker Section)

	// Logger Section
	LoggerSettings loggerSettings{};
	loggerSettings.logPath = _settings.logFilePath;

	try
	{
		_logger = std::make_unique<Logger>(loggerSettings);
		[[unlikely]] if (!_logger)
			return false;
	}
	catch (const std::runtime_error& re)
	{
		return false;
	}

	// Window Section
	WindowSettings settings{};
	settings.SetInstance(_settings.instance)
			.SetCmdShow(_settings.nCmdShow)
			.SetWindowProcedure(WindowProcedure)
			.SetClassName(L"Graphly Main Window")
			.SetTitle(L"Graphly")
			.SetDimension({ 800, 600 })
			.SetPosition({
				(SystemMetrics::GetScreenWidth() - settings.GetDimension().GetX()) / 2,
				(SystemMetrics::GetScreenHeight() - settings.GetDimension().GetY()) / 2
			})
			.AllowMultipleInstances(false);

	try
	{
		_window = std::make_unique<GraphlyWindow>(_logger.get(), settings);
		[[unlikely]] if (!_window)
			return false;
	}
	catch (const std::exception& e)
	{
		return false;
	}

	_logger->WriteLogMessage({ MessageType::Information, "App was initialized!\n" });
	return true;
}

App::~App()
{
	_logger->WriteLogMessage({ MessageType::Information, "App was destroyed!\n" });
}

bool App::AlreadyRunning()
{
	_mutex = CreateMutexW(NULL, TRUE, L"Graphly Instance");
	return GetLastError() == ERROR_ALREADY_EXISTS;
}

LRESULT CALLBACK App::WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			return 0;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProcW(hwnd, message, wParam, lParam);
}

int App::Run()
{
	_logger->WriteLogMessage({ MessageType::Information, "App running!\n" });
	return _window->Run();
}

std::string App::GetCurrentPath()
{
	return std::filesystem::current_path().string() + "\\";
}
