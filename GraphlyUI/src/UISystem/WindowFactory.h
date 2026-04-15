#ifndef GRAPHLYUI_WINDOWFACTORY_HEADER
#define GRAPHLYUI_WINDOWFACTORY_HEADER

#include "GraphlyUI/UISystem/Window/Window.h"
#include <memory>

namespace GraphlyUI
{
	class WindowFactory final
	{
	public:
		WindowFactory() = default;
		WindowFactory(const WindowFactory& other) = delete;
		WindowFactory(WindowFactory&& other) = delete;
		~WindowFactory() = default;

		[[nodiscard]] WindowPtr CreateWindowFromSettings(const WindowSettings& settings);
		[[nodiscard]] WindowPtr CreateWindowFromSettings(WindowSettings&& settings);

		WindowFactory& operator = (const WindowFactory& other) = delete;
		WindowFactory& operator = (WindowFactory&& other) = delete;
	};

	using WindowFactoryPtr = std::unique_ptr<WindowFactory>;
	using WindowFactorySharedPtr = std::shared_ptr<WindowFactory>;
}

#endif // GRAPHLYUI_WINDOWFACTORY_HEADER