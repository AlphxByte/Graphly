#ifndef GRAPHLYUI_EVENT_SYSTEM_HEADER
#define GRAPHLYUI_EVENT_SYSTEM_HEADER

#include "GraphlyUI/UISystem/Window/UIElement/UIElement.h"
#include "GraphlyUI/UISystem/Window/Window.h"
#include "UISystemEvent.h"

#include <queue>
#include <memory>

namespace GraphlyUI
{
	// TODO: support event propagation for ui elements
	class EventSystem final
	{
	public:
		EventSystem() = default;
		EventSystem(const EventSystem& other) = delete;
		EventSystem(EventSystem&& other) = delete;
		~EventSystem() = default;

		[[nodiscard]] UIElement* GetUITarget(UIElement* element, float mouseX, float mouseY);
		void ProcessUISystemEvents();
		void ProcessWindowEvents();
		void ProcessUIEvents();
		void PushUISystemEvent(const UISystemEvent& e);
		void PushUISystemEvent(UISystemEvent&& e);
		void PushWindowEvent(const WindowEvent& e);
		void PushWindowEvent(WindowEvent&& e);
		void PushUIEvent(const UIEvent& e);
		void PushUIEvent(UIEvent&& e);

		void UpdateHoveredElement(UIElement* current);
		void UpdateMousePosition(float x, float y);
		[[nodiscard]] float GetMouseX() const;
		[[nodiscard]] float GetMouseY() const;

		EventSystem& operator = (const EventSystem& other) = delete;
		EventSystem& operator = (EventSystem&& other) = delete;

	private:
		void DispatchUISystemEvent(const UISystemEvent& e);
		void DispatchWindowEvent(const WindowEvent& e);
		void DispatchUIEvent(UIEvent& e);
		bool RectHit(const GraphlyMath::Vector4& rect, float mouseX, float mouseY);

	private:
		std::deque<UISystemEvent> _uiSystemEventQueue{};
		std::deque<WindowEvent> _windowEventQueue{};
		std::deque<UIEvent> _uiEventQueue{};

		UIElement* _hoveredElement = nullptr;
		float _mouseX{}, _mouseY{};

	};

	using EventSystemPtr = std::unique_ptr<EventSystem>;
	using EventSystemSharedPtr = std::shared_ptr<EventSystem>;
}

#endif // GRAPHLYUI_EVENT_SYSTEM_HEADER
