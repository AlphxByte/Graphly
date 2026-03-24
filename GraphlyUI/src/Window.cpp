#include "WindowImpl.h"

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

    _impl->_settings = std::forward<WindowSettings>(settings);
    if (!_impl->Intialize())
        throw std::runtime_error("Window initialization failed.");
}

bool Window::WindowImpl::Intialize()
{
    // Window creation section
    Vector3 bgColor = _settings.backgroundColor;
    _backgroundBrush = CreateSolidBrush(RGB(bgColor.GetX(), bgColor.GetY(), bgColor.GetZ()));

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
    wcexw.hbrBackground = _backgroundBrush;
    wcexw.lpszClassName = _settings.className.c_str();

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
        this
    );
    if (!_hwnd)
        return false;

    ShowWindow(_hwnd, _settings.nCmdShow);

    // UIContext section
    try
    {
        _context = std::make_unique<UIContext>(_hwnd);
        [[unlikely]] if (!_context)
            return false;
    }
    catch (const std::runtime_error& e)
    {
        return false;
    }

    return true;
}

Window::~Window()
{
    if (_impl->_backgroundBrush)
        DeleteObject(_impl->_backgroundBrush);
}

int Window::Run()
{
    // Window main loop
    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return msg.wParam;
}

WindowSettings& Window::GetWindowSettings() const
{
    return _impl->_settings;
}

