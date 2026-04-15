#ifndef GRAPHLYUI_UICONTEXT_HEADER
#define GRAPHLYUI_UICONTEXT_HEADER

#include "UIFactory.h"

#include <memory>

namespace GraphlyUI
{
	class GraphicsSystem;

	class UIContext final
	{
	public:
		UIContext() = default;
		UIContext(const UIContext& other) = delete;
		UIContext(UIContext&& other) = delete;
		~UIContext() = default;

		void SetGraphicsSystem(GraphicsSystem* graphicsSystem);
		void SetUIFactory(UIFactory* uiFactory);
		[[nodiscard]] GraphicsSystem* GetGraphicsSystem();
		[[nodiscard]] UIFactory* GetUIFactory() const;

		UIContext& operator = (const UIContext& other) = delete;
		UIContext& operator = (UIContext&& other) = delete;

	private:
		// Not owned resources
		GraphicsSystem* _graphicsSystem{};
		UIFactory* _uiFactory{};
	};

	using UIContextPtr = std::unique_ptr<UIContext>;
	using UIContextSharedPtr = std::shared_ptr<UIContext>;
}

#endif // GRAPHLYUI_UICONTEXT_HEADER
