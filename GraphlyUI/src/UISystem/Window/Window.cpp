#include "WindowImpl.h"
#include "UIElement/UIElementImpl.h"
#include "../GraphicsSystem/GraphicsSystem.h"

using namespace GraphlyMath;
using namespace GraphlyUI;

Window::Window(const WindowSettings& settings)
{
    _impl = std::make_unique<WindowImpl>();
    [[unlikely]] if (!_impl)
        throw std::runtime_error("Window creation failed.");

    _impl->_settings = settings;
    if (!_impl->Intialize())
        throw std::runtime_error("Window initialization failed.");
}

Window::Window(WindowSettings&& settings)
{
    _impl = std::make_unique<WindowImpl>();
    [[unlikely]] if (!_impl)
        throw std::runtime_error("Window creation failed.");

    _impl->_settings = std::move(settings);
    if (!_impl->Intialize())
        throw std::runtime_error("Window initialization failed.");
}

bool Window::WindowImpl::Intialize()
{
    // Window creation section
    WNDCLASSEXW wcexw{};
    wcexw.cbSize       = sizeof(WNDCLASSEXW);
    wcexw.style        = CS_HREDRAW | CS_VREDRAW;
    wcexw.cbClsExtra   = 0;
    wcexw.cbWndExtra   = 0;
    wcexw.lpszMenuName = NULL;

    wcexw.hInstance     = _settings.instance;
    wcexw.lpfnWndProc   = _settings.procedure;
    wcexw.hIcon         = _settings.icon.icon;
    wcexw.hIconSm       = _settings.icon.iconSm;
    wcexw.hCursor       = _settings.cursor.cursor;
    wcexw.lpszClassName = _settings.className.c_str();
    wcexw.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    if (!GetClassInfoExW(_settings.instance, _settings.className.c_str(), &wcexw))
    {
        if (!RegisterClassExW(&wcexw))
            return false;
    }
    else
        return false;

    _hwnd = CreateWindowExW
    (
        static_cast<DWORD>(_settings.style.exStyleFlags),
        _settings.className.c_str(),
        _settings.title.c_str(),
        static_cast<DWORD>(_settings.style.styleFlags),
        _settings.position.GetX(), _settings.position.GetY(),
        _settings.dimension.GetX(), _settings.dimension.GetY(),
        HWND_DESKTOP,
        NULL,
        _settings.instance,
        _settings.data
    );
    if (!_hwnd)
        return false;

    ShowWindow(_hwnd, _settings.nCmdShow);

    // UIFactory section
    try
    {
        _factory = std::make_unique<UIFactory>();
        [[unlikely]] if (!_factory)
            return false;
    }
    catch (const std::runtime_error&)
    {
        return false;
    }

    // UIContext section
    try
    {
        _context = std::make_unique<UIContext>();
        [[unlikely]] if (!_context)
            return false;
        _context->SetUIFactory(_factory.get());
    }
    catch (const std::runtime_error&)
    {
        return false;
    }

    return true;
}

Window::~Window()
{

}

void Window::SetCloseFunction(WindowFunction closeFunction)
{
    _impl->_closeFunction = std::move(closeFunction);
}

void Window::SetMouseMoveFunction(WindowFunction mouseMoveFunction)
{
    _impl->_mouseMoveFunction = std::move(mouseMoveFunction);
}

void Window::SetMinimizeFunction(WindowFunction minimizeFunction)
{
    _impl->_minimizeFunction = std::move(minimizeFunction);
}

void Window::SetMaximizeFunction(WindowFunction maximizeFunction)
{
    _impl->_maximizeFunction = std::move(maximizeFunction);
}

void Window::SetResizeFunction(WindowFunction resizeFunction)
{
    _impl->_resizeFunction = std::move(resizeFunction);
}

void Window::OnClose(const WindowEvent& e)
{
    if (_impl->_closeFunction)
        _impl->_closeFunction(e);
}

void Window::OnMouseMove(const WindowEvent& e)
{
    if (_impl->_mouseMoveFunction)
        _impl->_mouseMoveFunction(e);
}

void Window::OnMinimize(const WindowEvent& e)
{
    if (_impl->_minimizeFunction)
        _impl->_minimizeFunction(e);
}

void Window::OnMaximize(const WindowEvent& e)
{
    if (_impl->_maximizeFunction)
        _impl->_maximizeFunction(e);
}

void Window::OnResize(const WindowEvent& e)
{
    if (_impl->_resizeFunction)
        _impl->_resizeFunction(e);
}

// Use GraphlyUI:: here to avoid name conflict
GraphlyUI::Rectangle* Window::GetRootElement() const
{
    return _impl->_root.get();
}

HWND Window::GetHWND() const
{
    return _impl->_hwnd;
}

const WindowSettings& Window::GetSettings() const
{
    return _impl->_settings;
}

void Window::Initialize(GraphicsSystem* graphics_system)
{
    _impl->_context->SetGraphicsSystem(graphics_system);

    RECT rect{};
    GetClientRect(_impl->_hwnd, &rect);

    UIElementSettings rootSettings;
    rootSettings.backgroundColor = Vector4(255.0f, 0.0f, 0.0f, 1.0f);
    rootSettings.dimension = Vector2(rect.right - rect.left, rect.bottom - rect.top);

    try
    {
        // Unique ptr cant call the private constructor of Rectangle so use new
        _impl->_root.reset(new Rectangle(_impl->_context.get(), "root", rootSettings));
        [[unlikely]] if (!_impl->_root)
            throw std::runtime_error("Failed to create the root element.");
    }
    catch (const std::runtime_error&)
    {
        throw;
    }

    _impl->_root->SetResizeFunction([](const UIEvent& e)
    {
        UINT width = LOWORD(e.lParam);
        UINT height = HIWORD(e.lParam);

        e.target->SetDimension(Vector2(width, height));
    });
}