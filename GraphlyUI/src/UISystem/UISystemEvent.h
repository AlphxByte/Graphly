#ifndef GRAPHLYUI_UI_SYSTEM_EVENT_HEADER
#define GRAPHLYUI_UI_SYSTEM_EVENT_HEADER

#include <windows.h>

namespace GraphlyUI
{
	class UISystem;

	enum class UISystemEventType
	{
		None,
		Resize
	};

	struct UISystemEvent final
	{
		UISystemEventType type = UISystemEventType::None;
		UISystem* uiSystem = nullptr;
		HWND hwnd = nullptr;
		WPARAM wParam{};
		LPARAM lParam{};
	};
}

#endif // GRAPHLYUI_UI_SYSTEM_EVENT_HEADER