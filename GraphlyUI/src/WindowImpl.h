#ifndef GRAPHLYUI_WINDOWIMPL_HEADER
#define GRAPHLYUI_WINDOWIMPL_HEADER

#include "../include/GraphlyUI/Window.h"
#include "UIContext.h"
#include "GraphlyCore/Logger.h"

namespace GraphlyUI
{
	struct Window::WindowImpl
	{
		WindowImpl() = default;
		WindowImpl(const WindowImpl& other) = delete;
		WindowImpl(WindowImpl&& other) = delete;
		~WindowImpl() = default;

		bool Intialize();

		WindowImpl& operator = (const WindowImpl& other) = delete;
		WindowImpl& operator = (WindowImpl&& other) = delete;

		// Window Members
		WindowSettings _settings{};
		UIContextPtr _context{};
		HWND _hwnd{};
		HBRUSH _backgroundBrush{};
	};
}

#endif // GRAPHLYUI_WINDOWIMPL_HEADER
