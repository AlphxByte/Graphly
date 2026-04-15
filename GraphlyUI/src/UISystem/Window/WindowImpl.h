#ifndef GRAPHLYUI_WINDOWIMPL_HEADER
#define GRAPHLYUI_WINDOWIMPL_HEADER

#include "GraphlyUI/UISystem/Window/Window.h"
#include "GraphlyUI/UISystem/Window/UIElement/Rectangle.h"
#include "UIContext.h"

namespace GraphlyUI
{
	class GraphicsSystem;

	struct Window::WindowImpl
	{
		WindowImpl() = default;
		WindowImpl(const WindowImpl& other) = delete;
		WindowImpl(WindowImpl&& other) = delete;
		~WindowImpl() = default;

		[[nodiscard]] bool Intialize();

		WindowImpl& operator = (const WindowImpl& other) = delete;
		WindowImpl& operator = (WindowImpl&& other) = delete;

		// Window Members
		WindowSettings _settings{};
		HWND _hwnd{};

		// Functions
		WindowFunction _closeFunction{};
		WindowFunction _mouseMoveFunction{};
		WindowFunction _minimizeFunction{};
		WindowFunction _maximizeFunction{};
		WindowFunction _resizeFunction{};
		
		// Components
		UIFactoryPtr _factory{};
		UIContextPtr _context{};
		RectanglePtr _root{};
	};
}

#endif // GRAPHLYUI_WINDOWIMPL_HEADER
