#ifndef GRAPHLYUI_UIFACTORY_HEADER
#define GRAPHLYUI_UIFACTORY_HEADER

#include "GraphlyUI/UISystem/Window/UIElement/UIElement.h"

#include <windows.h>
#include <string>

namespace GraphlyUI
{
	class UIFactory final
	{
	public:
		UIFactory() = default;
		UIFactory(const UIFactory& other) = delete;
		UIFactory(UIFactory&& other) = delete;
		~UIFactory() = default;

		template<typename T, typename... Args>
		[[nodiscard]] UIElementPtr CreateUIElement(Args&&... args)
		{
			return std::make_unique<T>(std::forward<Args>(args)...);
		}

		UIFactory& operator = (const UIFactory& other) = delete;
		UIFactory& operator = (UIFactory&& other) = delete;
	};

	using UIFactoryPtr       = std::unique_ptr<UIFactory>;
	using UIFactorySharedPtr = std::shared_ptr<UIFactory>;
}

#endif // GRAPHLYUI_UIFACTORY_HEADER
