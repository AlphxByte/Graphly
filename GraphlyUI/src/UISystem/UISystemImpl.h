#ifndef GRAPHLYUI_UISYSTEM_IMPL_HEADER
#define GRAPHLYUI_UISYSTEM_IMPL_HEADER

#include "GraphlyUI/UISystem/UISystem.h"
#include "WindowFactory.h"
#include "GraphicsSystem/GraphicsSystem.h"
#include "UIRenderer.h"
#include "EventSystem.h"

#include <unordered_map>

namespace GraphlyUI
{
	struct UISystem::UISystemImpl
	{
		using WindowIterator = std::unordered_map<std::string, WindowPtr>::iterator;
		using WindowConstIterator = std::unordered_map<std::string, WindowPtr>::const_iterator;

		UISystemImpl() = default;
		UISystemImpl(const UISystemImpl& other) = delete;
		UISystemImpl(UISystemImpl&& other) = delete;
		~UISystemImpl() = default;

		void Resize(const UISystemEvent& e);
		[[nodiscard]] bool Initialize();

		UISystemImpl& operator = (const UISystemImpl& other) = delete;
		UISystemImpl& operator = (UISystemImpl&& other) = delete;

		// Members Section
		UISystemSettings _settings{};
		bool _running = true;

		WindowFactoryPtr _factory{};
		GraphicsSystemPtr _graphicsSystem{};
		UIRendererPtr _renderer{};
		EventSystemPtr _eventSystem{};
		std::unordered_map<std::string, WindowPtr> _windows{};
	};
}

#endif // GRAPHLYUI_UISYSTEM_IMPL_HEADER
