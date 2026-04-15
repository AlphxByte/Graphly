#ifndef GRAPHLYUI_WINDOW_EVENT_HEADER
#define GRAPHLYUI_WINDOW_EVENT_HEADER

#include "../../GraphlyUIExports.h"

#include <windows.h>

namespace GraphlyUI
{
	class Window;

	enum class WindowEventType
	{
		None, 
		Close,
		MouseMove,
		Minimize,
		Maximize,
		Resize
	};

	struct GRAPHLYUI_API WindowEvent final
	{
		Window* target = nullptr;
		WindowEventType type = WindowEventType::None;
		float mouseX{}, mouseY{};
		WPARAM wParam{};
		LPARAM lParam{};
	};
}

#endif // GRAPHLYUI_WINDOW_EVENT_HEADER
