#ifndef GRAPHLYUI_UIFACTORY_HEADER
#define GRAPHLYUI_UIFACTORY_HEADER

#include "../include/GraphlyUI/UIElement.h"
#include "../include/GraphlyUI/TextField.h"
#include "../include/GraphlyUI/Button.h"
#include "../include/GraphlyUI/Image.h"

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
