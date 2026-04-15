#include "Graphly/Application/Application.h"

#include <filesystem>

using namespace Graphly;
using namespace GraphlyUI;
using namespace GraphlyMath;

HANDLE Application::_mutex = nullptr;

Application::Application(const ApplicationSettings& settings)
{
	_settings = settings;
	[[unlikely]] if (!Initialize())
		throw std::runtime_error("Application initialization failed.");
}

Application::Application(ApplicationSettings&& settings)
{
	_settings = std::forward<ApplicationSettings>(settings);
	[[unlikely]] if (!Initialize())
		throw std::runtime_error("Application initialization failed.");
}

bool Application::Initialize()
{
	// Logger Section
	LoggerSettings loggerSettings{};
	loggerSettings.logPath = _settings.logFilePath;

	try
	{
		_logger = std::make_unique<Logger>(loggerSettings);
		[[unlikely]] if (!_logger)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	// UISystem Section
	UISystemSettings uiSystemSettings{};
	uiSystemSettings.graphicsSettings.adapterSettings.preference = AdapterPreference::LowPower;
	uiSystemSettings.graphicsSettings.vsync = true;

	try
	{
		_uiSystem = std::make_unique<UISystem>(uiSystemSettings);
		[[unlikely]] if (!_uiSystem)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	// Window Section
	WindowSettings windowSettings{};
	windowSettings.SetInstance(_settings.instance)
		.SetCmdShow(_settings.nCmdShow)
		.SetWindowProcedure(GraphlyMainWindowProcedure)
		.SetClassName(L"Graphly Main Window")
		.SetTitle(L"Graphly")
		.SetDimension({ 800, 600 })
		.SetPosition
		({
			(SystemMetrics::GetScreenWidth() - windowSettings.GetDimension().GetX()) / 2,
			(SystemMetrics::GetScreenHeight() - windowSettings.GetDimension().GetY()) / 2
		})
		.SetData(this)
		.AllowMultipleInstances(false);

	try
	{
		_mainWindow = _uiSystem->CreateWindowFromSettings<GraphlyMainWindow>("Graphly Main Window", _logger.get(), windowSettings);
		[[unlikely]] if (!_mainWindow)
			return false;
	}
	catch (const std::exception&)
	{
		return false;
	}

	TextFormatSettings textFormatSettings{};
	textFormatSettings.fontFamily = L"Segoe UI";
	textFormatSettings.fontSize = 10.0f;
	_uiSystem->CreateTextFormat("default", textFormatSettings);

	UIElementSettings childSettings{};
	childSettings.backgroundColor = Vector4(0.0f, 0.0f, 255.0f, 1.0f);
	childSettings.dimension = Vector2(100.0f, 100.0f);
	childSettings.transform.SetTranslation(Vector2(20.0f, 20.0f));
	_childElement = _mainWindow->GetRootElement()->CreateUIElement<GraphlyUI::Rectangle>("child", childSettings);

	// Second child coordinates are relative to the parent not the window
	TextElementSettings secondChildSettings{};
	secondChildSettings.ui.backgroundColor = Vector4(0.0f, 255.0f, 0.0f, 1.0f);
	secondChildSettings.ui.dimension = Vector2(40.0f, 40.0f);
	secondChildSettings.ui.transform.SetTranslation(Vector2(10.0f, 10.0f));
	secondChildSettings.ui.alignment = UIElementAlignment::Center;

	secondChildSettings.textSettings.str = L"Hello!";
	secondChildSettings.textSettings.textFormatName = "default";
	secondChildSettings.textSettings.textLayoutSettings.textAlignment = TextAlignment::Center;
	secondChildSettings.textSettings.textLayoutSettings.paragraphAlignment = ParagraphAlignment::Center;
	secondChildSettings.textSettings.renderBackground = true;
	_secondChild = _childElement->CreateUIElement<GraphlyUI::Text>("hello world text", secondChildSettings);

	ButtonElementSettings buttonSettings{};
	buttonSettings.ui.backgroundColor = Vector4(255.0f, 255.0f, 0.0f, 1.0f);
	buttonSettings.ui.dimension = Vector2(50.0f, 50.0f);
	buttonSettings.ui.alignment = UIElementAlignment::Center;

	buttonSettings.buttonSettings.textSettings.str = L"Click me";
	buttonSettings.buttonSettings.textSettings.textFormatName = "default";
	buttonSettings.buttonSettings.textSettings.textLayoutSettings.textAlignment = TextAlignment::Center;
	buttonSettings.buttonSettings.textSettings.textLayoutSettings.paragraphAlignment = ParagraphAlignment::Center;
	_button = _mainWindow->GetRootElement()->CreateUIElement<Button>("button", buttonSettings);

	_button->SetLeftButtonDownFunction([](const UIEvent& e)
	{
		MessageBoxW(HWND_DESKTOP, L"TEST", L"TEST", MB_OK);
	});

	_secondChild->SetMouseEnterFunction([](const UIEvent& e)
	{
		e.target->SetBackgroundColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	});
	_secondChild->SetMouseLeaveFunction([](const UIEvent& e)
	{
		e.target->SetBackgroundColor(Vector4(0.0f, 255.0f, 0.0f, 1.0f));
	});

	_logger->WriteLogMessage({ MessageType::Information, "Application initialized!\n" });
	return true;
}

Application::~Application()
{
	_logger->WriteLogMessage({ MessageType::Information, "Application destroyed!\n" });
}

bool Application::AlreadyRunning()
{
	_mutex = CreateMutexW(NULL, TRUE, L"Graphly Instance");
	return GetLastError() == ERROR_ALREADY_EXISTS;
}

LRESULT CALLBACK Application::GraphlyMainWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Application* application = nullptr;
	if (message == WM_NCCREATE)
		Window::SetWindowData<Application>(hwnd, lParam, application);
	application = Window::GetWindowData<Application>(hwnd);

	if (!application)
		return DefWindowProcW(hwnd, message, wParam, lParam);

	switch (message)
	{
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			return 0;
		}
		case WM_DESTROY:
		{
			application->_uiSystem->Quit(0);
			return 0;
		}
		default:
		{
			application->_uiSystem->PushEvent(application->_mainWindow, message, wParam, lParam);
			break;
		}
	}

	return DefWindowProcW(hwnd, message, wParam, lParam);
}

int Application::Run()
{
	_logger->WriteLogMessage({ MessageType::Information, "Application running!\n" });

	while (_uiSystem->IsRunning())
	{
		_uiSystem->Run();

		_uiSystem->BeginFrame();
		_uiSystem->ProcessEvents();
		_uiSystem->Render(_mainWindow);
		_uiSystem->EndFrame();
	}

	return 0;
}

std::string Application::GetCurrentPath()
{
	return std::filesystem::current_path().string() + "\\";
}
