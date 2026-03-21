#ifndef GRAPHLYUI_UICONTEXT_HEADER
#define GRAPHLYUI_UICONTEXT_HEADER

#include "UIFactory.h"
#include "../include/GraphlyUI/UIElement.h"

namespace GraphlyUI
{
	class UIContext final
	{
	public:
		UIContext(HWND hwnd);
		UIContext(const UIContext& other) = delete;
		UIContext(UIContext&& other) = delete;
		~UIContext() = default;

		[[nodiscard]] UIElement* GetRoot() const;

		UIContext& operator = (const UIContext& other) = delete;
		UIContext& operator = (UIContext&& other) = delete;

	private:
		UIFactoryPtr _factory{};
		UIElementPtr _root{};
		HWND _hwnd{};
	};

	using UIContextPtr = std::unique_ptr<UIContext>;
	using UIContextSharedPtr = std::shared_ptr<UIContext>;
}

#endif // GRAPHLYUI_UICONTEXT_HEADER
