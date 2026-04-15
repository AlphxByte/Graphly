#include "UISystemImpl.h"
#include "GraphlyUI/UISystem/Window/Window.h"
#include "UISystemEvent.h"

#include <windowsx.h>

using namespace GraphlyUI;
using namespace GraphlyMath;

UISystem::UISystem(const UISystemSettings& settings)
{
	_impl = std::make_unique<UISystemImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("UISystem implementation creation failed.");

	_impl->_settings = settings;
	if (!_impl->Initialize())
		throw std::runtime_error("UISystem initialization failed.");
}

UISystem::UISystem(UISystemSettings&& settings)
{
	_impl = std::make_unique<UISystemImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("UISystem implementation creation failed.");

	_impl->_settings = std::move(settings);
	if (!_impl->Initialize())
		throw std::runtime_error("UISystem initialization failed.");
}

bool UISystem::UISystemImpl::Initialize()
{
	// Factory Section
	try
	{
		_factory = std::make_unique<WindowFactory>();
		[[unlikely]] if (!_factory)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	// GraphicsSystem Section
	try
	{
		_graphicsSystem = std::make_unique<GraphicsSystem>(_settings.graphicsSettings);
		if (!_graphicsSystem)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	// UIRenderer Section
	try
	{
		_renderer = std::make_unique<UIRenderer>(_graphicsSystem.get());
		if (!_renderer)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	// EventSystem Section
	try
	{
		_eventSystem = std::make_unique<EventSystem>();
		[[unlikely]] if (!_eventSystem)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	return true;
}

UISystem::~UISystem()
{

}

bool UISystem::IsRunning()
{
	return _impl->_running;
}

void UISystem::Run()
{
	MSG msg{};
	while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			_impl->_running = false;

		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

void UISystem::UISystemImpl::Resize(const UISystemEvent& e)
{
	UINT width = LOWORD(e.lParam);
	UINT height = HIWORD(e.lParam);

	if (width > 0 && height > 0)
		_graphicsSystem->ResizeSwapChain(e.hwnd, width, height);
}

void UISystem::Quit(int exitCode)
{
	PostQuitMessage(exitCode);
}

// TODO: Calculate delta time
void UISystem::BeginFrame()
{

}

void UISystem::Render(Window* window)
{
	_impl->_graphicsSystem->BeginDraw(window);
	_impl->_renderer->Render(window->GetRootElement());
	_impl->_graphicsSystem->EndDraw(window);
}

// TODO: Make a proper way to slow down based on vsync
void UISystem::EndFrame()
{
	Sleep(1); // Reduce cpu usage
}

void UISystem::PushEvent(Window* window, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!window)
		return;

	UISystemEvent uiSystemEvent{};
	uiSystemEvent.uiSystem = this;
	uiSystemEvent.hwnd = window->GetHWND();
	uiSystemEvent.wParam = wParam;
	uiSystemEvent.lParam = lParam;

	WindowEvent windowEvent{};
	windowEvent.target = window;
	windowEvent.wParam = wParam;
	windowEvent.lParam = lParam;

	UIEvent uiEvent{};
	uiEvent.window = window;
	uiEvent.wParam = wParam;
	uiEvent.lParam = lParam;

	switch (message)
	{
		case WM_SIZE:
		{
			uiSystemEvent.type = UISystemEventType::Resize;
			_impl->_eventSystem->PushUISystemEvent(uiSystemEvent);

			windowEvent.type = WindowEventType::Resize;
			_impl->_eventSystem->PushWindowEvent(windowEvent);

			uiEvent.target = window->GetRootElement();
			uiEvent.type = UIEventType::Resize;
			_impl->_eventSystem->PushUIEvent(uiEvent);

			break;
		}

		case WM_MOUSEMOVE:
		{
			windowEvent.mouseX = GET_X_LPARAM(lParam);
			windowEvent.mouseY = GET_Y_LPARAM(lParam);
			windowEvent.type = WindowEventType::MouseMove;
			_impl->_eventSystem->UpdateMousePosition(windowEvent.mouseX, windowEvent.mouseY);
			_impl->_eventSystem->PushWindowEvent(windowEvent);

			break;
		}

		case WM_LBUTTONDOWN:
		{
			uiEvent.mouseX = GET_X_LPARAM(lParam);
			uiEvent.mouseY = GET_Y_LPARAM(lParam);
			uiEvent.type = UIEventType::LeftButtonDown;
			_impl->_eventSystem->PushUIEvent(uiEvent);

			break;
		}
	}
}

void UISystem::ProcessEvents()
{
	_impl->_eventSystem->ProcessUISystemEvents();
	_impl->_eventSystem->ProcessWindowEvents();
	_impl->_eventSystem->ProcessUIEvents();
}

void UISystem::CreateTextFormat(std::string_view name, const TextFormatSettings& settings)
{
	_impl->_graphicsSystem->GetTextSystem()->CreateTextFormat(name, settings);
}

void UISystem::CreateTextFormat(std::string_view name, TextFormatSettings&& settings)
{
	_impl->_graphicsSystem->GetTextSystem()->CreateTextFormat(name, std::move(settings));
}

Window* UISystem::CreateWindowFromSettings(std::string_view name, const WindowSettings& settings)
{
	UISystemImpl::WindowIterator it = _impl->_windows.find(std::string(name));
	if (it != _impl->_windows.end())
		return it->second.get();

	std::unique_ptr<Window> window;
	try
	{
		window = _impl->_factory->CreateWindowFromSettings(settings);
		window->Initialize(_impl->_graphicsSystem.get());
		_impl->_graphicsSystem->CreateSwapChain(window->GetHWND());
	}
	catch (const std::runtime_error&)
	{
		return nullptr;
	}

	return _impl->_windows.emplace(name, std::move(window)).first->second.get();
}

Window* UISystem::CreateWindowFromSettings(std::string_view name, WindowSettings&& settings)
{
	UISystemImpl::WindowIterator it = _impl->_windows.find(std::string(name));
	if (it != _impl->_windows.end())
		return it->second.get();

	std::unique_ptr<Window> window;
	try
	{
		window = _impl->_factory->CreateWindowFromSettings(std::forward<WindowSettings>(settings));
		window->Initialize(_impl->_graphicsSystem.get());
		_impl->_graphicsSystem->CreateSwapChain(window->GetHWND());
	}
	catch (const std::runtime_error&)
	{
		return nullptr;
	}

	return _impl->_windows.emplace(name, std::move(window)).first->second.get();
}

bool UISystem::DestroyWindow(std::string_view name)
{
	UISystemImpl::WindowIterator it = _impl->_windows.find(std::string(name));
	if (it == _impl->_windows.end())
		return false;

	if (!_impl->_graphicsSystem->DestroySwapChain(it->second.get()->GetHWND()))
		return false;
	_impl->_windows.erase(it);

	return true;
}

Window* UISystem::GetWindow(std::string_view name)
{
	UISystemImpl::WindowConstIterator it = _impl->_windows.find(std::string(name));
	if (it == _impl->_windows.end())
		return nullptr;
	return it->second.get();
}

GraphicsSystem* UISystem::GetGraphicsSystem() const
{
	return _impl->_graphicsSystem.get();
}

void UISystem::CreateWindowFromSettingsImpl(std::string_view name, std::unique_ptr<Window> window)
{
	UISystemImpl::WindowIterator it = _impl->_windows.find(std::string(name));
	if (it != _impl->_windows.end())
		return;

	_impl->_graphicsSystem->CreateSwapChain(window->GetHWND());
	_impl->_windows.emplace(name, std::move(window));
}
