#ifndef GRAPHLYUI_UIFACTORY_HEADER
#define GRAPHLYUI_UIFACTORY_HEADER

#include "GraphlyUI/Window/UIElement/UIElement.h"
#include "GraphlyUI/Window/UIElement/TextField.h"
#include "GraphlyUI/Window/UIElement/Button.h"
#include "GraphlyUI/Window/UIElement/Image.h"

#include <windows.h>
#include <string>

namespace GraphlyUI
{
	class UIFactory final
	{
	public:
		UIFactory(HWND hwnd);
		UIFactory(const UIFactory& other) = delete;
		UIFactory(UIFactory&& other) = delete;
		~UIFactory() = default;

		[[nodiscard]] UIElementPtr CreateUIElement(std::string_view name, const UIElementSettings& settings);
		[[nodiscard]] UIElementPtr CreateUIElement(std::string_view name, UIElementSettings&& settings);

		[[nodiscard]] HWND GetHWND() const;

		UIFactory& operator = (const UIFactory& other) = delete;
		UIFactory& operator = (UIFactory&& other) = delete;

	private:
		HWND _hwnd;
	};

	using UIFactoryPtr       = std::unique_ptr<UIFactory>;
	using UIFactorySharedPtr = std::shared_ptr<UIFactory>;
}

#endif // GRAPHLYUI_UIFACTORY_HEADER
