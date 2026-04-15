#include "EventSystem.h"
#include "GraphlyUI/UISystem/Window/Window.h"
#include "UISystemImpl.h"

using namespace GraphlyUI;
using namespace GraphlyMath;

UIElement* EventSystem::GetUITarget(UIElement* element, float mouseX, float mouseY)
{
	float x = element->GetWorldTransform().dx;
	float y = element->GetWorldTransform().dy;
	float w = element->GetUISettings().dimension.GetX();
	float h = element->GetUISettings().dimension.GetY();

	if (!RectHit(Vector4(x, y, x + w, y + h), mouseX, mouseY))
		return nullptr;

	for (const auto& [name, child] : *element)
	{
		UIElement* hit = GetUITarget(child.get(), mouseX, mouseY);
		if (hit)
			return hit;
	}

	if (!element->IsInteractable())
		return nullptr;
	return element;
}

void EventSystem::ProcessUISystemEvents()
{
	while (!_uiSystemEventQueue.empty())
	{
		UISystemEvent e = _uiSystemEventQueue.front();
		_uiSystemEventQueue.pop_front();
		DispatchUISystemEvent(e);
	}
}

void EventSystem::ProcessWindowEvents()
{
	while (!_windowEventQueue.empty())
	{
		WindowEvent e = _windowEventQueue.front();
		_windowEventQueue.pop_front();
		DispatchWindowEvent(e);
	}
}

void EventSystem::ProcessUIEvents()
{
	while (!_uiEventQueue.empty())
	{
		UIEvent e = _uiEventQueue.front();
		_uiEventQueue.pop_front();
		DispatchUIEvent(e);
	}
}

void EventSystem::PushUISystemEvent(const UISystemEvent& e)
{
	_uiSystemEventQueue.push_back(e);
}

void EventSystem::PushUISystemEvent(UISystemEvent&& e)
{
	_uiSystemEventQueue.push_back(std::move(e));
}

void EventSystem::PushWindowEvent(const WindowEvent& e)
{
	_windowEventQueue.push_back(e);
}

void EventSystem::PushWindowEvent(WindowEvent&& e)
{
	_windowEventQueue.push_back(std::move(e));
}

void EventSystem::PushUIEvent(const UIEvent& e)
{
	_uiEventQueue.push_back(e);
}

void EventSystem::PushUIEvent(UIEvent&& e)
{
	_uiEventQueue.push_back(std::move(e));
}

void EventSystem::DispatchUISystemEvent(const UISystemEvent& e)
{
	switch (e.type)
	{
		case UISystemEventType::Resize:
		{
			e.uiSystem->_impl->Resize(e);
			break;
		}
	}
}

void EventSystem::DispatchWindowEvent(const WindowEvent& e)
{
	switch (e.type)
	{
		case WindowEventType::Close:
		{
			e.target->OnClose(e);
			break;
		}
		case WindowEventType::MouseMove:
		{
			UIElement* target = GetUITarget(e.target->GetRootElement(), e.mouseX, e.mouseY);
			UIEvent uiEvent{};
			uiEvent.wParam = e.wParam;
			uiEvent.lParam = e.lParam;
			uiEvent.window = e.target;
			uiEvent.mouseX = e.mouseX;
			uiEvent.mouseY = e.mouseY;
			uiEvent.target = target;
			uiEvent.type = UIEventType::MouseMove;
			target->OnMouseMove(uiEvent);

			if (target != _hoveredElement)
			{
				if (_hoveredElement)
				{
					uiEvent.type = UIEventType::MouseLeave;
					uiEvent.target = _hoveredElement;
					if (_hoveredElement)
						_hoveredElement->OnMouseLeave(uiEvent);

					uiEvent.type = UIEventType::MouseLeave;
					uiEvent.target = target;
					target->OnMouseLeave(uiEvent);
				}

				if (target)
				{
					uiEvent.type = UIEventType::MouseEnter;
					uiEvent.target = target;
					if (_hoveredElement)
						target->OnMouseEnter(uiEvent);
				}

				_hoveredElement = target;
			}

			e.target->OnMouseMove(e);
			break;
		}
		case WindowEventType::Minimize:
		{
			e.target->OnMinimize(e);
			break;
		}
		case WindowEventType::Maximize:
		{
			e.target->OnMaximize(e);
			break;
		}
		case WindowEventType::Resize:
		{
			e.target->OnResize(e);
			break;
		}
	}
}

void EventSystem::DispatchUIEvent(UIEvent& e)
{
	if (!e.target)
		e.target = GetUITarget(e.window->GetRootElement(), _mouseX, _mouseY);

	switch (e.type)
	{
		case UIEventType::LeftButtonDown:
		{
			e.target->OnLeftButtonDown(e);
			break;
		}
		case UIEventType::LeftButtonUp:
		{
			e.target->OnLeftButtonUp(e);
			break;
		}
		case UIEventType::RightButtonDown:
		{
			e.target->OnRightButtonDown(e);
			break;
		}
		case UIEventType::RightButtonUp:
		{
			e.target->OnRightButtonUp(e);
			break;
		}
		case UIEventType::MouseEnter:
		{
			e.target->OnMouseEnter(e);
			break;
		}
		case UIEventType::MouseLeave:
		{
			e.target->OnMouseLeave(e);
			break;
		}
		case UIEventType::Active:
		{
			e.target->OnActive(e);
			break;
		}
		case UIEventType::Resize:
		{
			e.target->OnResize(e);
			break;
		}
	}
}

bool EventSystem::RectHit(const Vector4& rect, float mouseX, float mouseY)
{
	return mouseX >= rect.GetX() && mouseX <= rect.GetZ()
		&& mouseY >= rect.GetY() && mouseY <= rect.GetW();
}

void EventSystem::UpdateHoveredElement(UIElement* current)
{
	_hoveredElement = current;
}

void EventSystem::UpdateMousePosition(float x, float y)
{
	_mouseX = x;
	_mouseY = y;
}

float EventSystem::GetMouseX() const
{
	return _mouseX;
}

float EventSystem::GetMouseY() const
{
	return _mouseY;
}
