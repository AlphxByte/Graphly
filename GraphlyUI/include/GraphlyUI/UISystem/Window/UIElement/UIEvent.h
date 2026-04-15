#ifndef GRAPHLYUI_UI_EVENT_HEADER
#define GRAPHLYUI_UI_EVENT_HEADER

#include "../../../GraphlyUIExports.h"

#include <windows.h>

namespace GraphlyUI
{
	class UIElement;
	class Window;

	enum class UIEventType
	{
		None,
		LeftButtonDown,
		LeftButtonUp,
		RightButtonDown,
		RightButtonUp,
		MouseMove,
		MouseEnter,
		MouseLeave,
		Active,
		Resize
	};

	struct GRAPHLYUI_API UIEvent
	{
		Window* window = nullptr;
		UIElement* target = nullptr;
		UIEventType type = UIEventType::None;
		float mouseX{}, mouseY{};
		WPARAM wParam{};
		LPARAM lParam{};
	};
}

#endif // GRAPHLYUI_UI_EVENT_HEADER