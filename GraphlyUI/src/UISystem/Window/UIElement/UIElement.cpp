#include "UIElementImpl.h"
#include "../UIContext.h"
#include "../../GraphicsSystem/GraphicsSystem.h"
#include "GraphlyMath/GraphlyMath.h"

#include <queue>
#include <stdexcept>

using namespace GraphlyUI;
using namespace GraphlyMath;

UIElement::UIElement(std::string_view name, const UIElementSettings& settings)
{
	_impl = std::make_unique<UIElementImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("UIElement initialization failed.");

	_impl->_settings = settings;
	_impl->_name = std::string(name);
}

UIElement::UIElement(std::string_view name, UIElementSettings&& settings)
{
	_impl = std::make_unique<UIElementImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("UIElement initialization failed.");

	_impl->_settings = std::move(settings);
	_impl->_name = std::string(name);
}

// Root constructors
UIElement::UIElement(UIContext* context, std::string_view name, const UIElementSettings& settings)
{
	_impl = std::make_unique<UIElementImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("UIElement initialization failed.");

	_impl->_settings = settings;
	_impl->_parent = nullptr;
	_impl->_context = context;
	_impl->_name = std::string(name);

	try
	{
		_impl->_brush = std::make_unique<SolidColorBrush>
			(
				_impl->_context->GetGraphicsSystem()->GetD2DSystem()->GetD2DDevice(),
				_impl->_settings.backgroundColor
			);
		if (!_impl)
			throw std::runtime_error("SolidColorBrush failed to initialize.");
	}
	catch (const std::runtime_error&)
	{
		throw;
	}
}

UIElement::UIElement(UIContext* context, std::string_view name, UIElementSettings&& settings)
{
	_impl = std::make_unique<UIElementImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("UIElement initialization failed.");

	_impl->_settings = std::move(settings);
	_impl->_parent = nullptr;
	_impl->_context = context;
	_impl->_name = std::string(name);

	try
	{
		_impl->_brush = std::make_unique<SolidColorBrush>
			(
				_impl->_context->GetGraphicsSystem()->GetD2DSystem()->GetD2DDevice(),
				_impl->_settings.backgroundColor
			);
		if (!_impl)
			throw std::runtime_error("SolidColorBrush failed to initialize.");
	}
	catch (const std::runtime_error&)
	{
		throw;
	}
}

UIElement::~UIElement()
{

}

void UIElement::SetAlignment(UIElement* elem)
{
	UIElementAlignment alignment = elem->_impl->_settings.alignment;
	if (alignment == UIElementAlignment::None)
		return;

	float w = elem->_impl->_settings.dimension.GetX();
	float h = elem->_impl->_settings.dimension.GetY();
	float wParent = elem->_impl->_parent->_impl->_settings.dimension.GetX();
	float hParent = elem->_impl->_parent->_impl->_settings.dimension.GetY();

	switch (alignment)
	{
	case UIElementAlignment::TopLeft:
		elem->_impl->_settings.transform.SetTranslation(Vector2(0.0f, 0.0f));
		break;
	case UIElementAlignment::TopRight:
		elem->_impl->_settings.transform.SetTranslation(Vector2(wParent - w, 0.0f));
		break;
	case UIElementAlignment::TopCenter:
		elem->_impl->_settings.transform.SetTranslation(Vector2((wParent - w) / 2, 0.0f));
		break;
	case UIElementAlignment::CenterLeft:
		elem->_impl->_settings.transform.SetTranslation(Vector2(0.0f, (hParent - h) / 2));
		break;
	case UIElementAlignment::Center:
		elem->_impl->_settings.transform.SetTranslation(Vector2((wParent - w) / 2, (hParent - h) / 2));
		break;
	case UIElementAlignment::CenterRight:
		elem->_impl->_settings.transform.SetTranslation(Vector2(wParent - w, (hParent - h) / 2));
		break;
	case UIElementAlignment::BottomLeft:
		elem->_impl->_settings.transform.SetTranslation(Vector2(0.0f, hParent - h));
		break;
	case UIElementAlignment::BottomRight:
		elem->_impl->_settings.transform.SetTranslation(Vector2(wParent - w, hParent - h));
		break;
	case UIElementAlignment::BottomCenter:
		elem->_impl->_settings.transform.SetTranslation(Vector2((wParent - w) / 2, hParent - h));
		break;
	}
}

void UIElement::Render()
{
	// Use local space
	_impl->_context
	->GetGraphicsSystem()
	->GetD2DSystem()
	->GetD2DDevice()
	->FillRectangle
	(
		Vector4
		(
			0.0f,
			0.0f,
			_impl->_settings.dimension.GetX(),
			_impl->_settings.dimension.GetY()
		), 
		_impl->_brush.get()
	);
}

void UIElement::SetLeftButtonDownFunction(UIFunction leftButtonDownFunction)
{
	_impl->_leftButtonDownFunction = std::move(leftButtonDownFunction);
}

void UIElement::SetLeftButtonUpFunction(UIFunction leftButtonUpFunction)
{
	_impl->_leftButtonUpFunction = std::move(leftButtonUpFunction);
}

void UIElement::SetRightButtonDownFunction(UIFunction rightButtonDownFunction)
{
	_impl->_rightButtonDownFunction = std::move(rightButtonDownFunction);
}

void UIElement::SetRightButtonUpFunction(UIFunction rightButtonUpFunction)
{
	_impl->_rightButtonUpFunction = std::move(rightButtonUpFunction);
}

void UIElement::SetMouseMoveFunction(UIFunction mouseMoveFunction)
{
	_impl->_mouseMoveFunction = std::move(mouseMoveFunction);
}

void UIElement::SetMouseEnterFunction(UIFunction mouseEnterFunction)
{
	_impl->_mouseEnterFunction = std::move(mouseEnterFunction);
}

void UIElement::SetMouseLeaveFunction(UIFunction mouseLeaveFunction)
{
	_impl->_mouseLeaveFunction = std::move(mouseLeaveFunction);
}

void UIElement::SetActiveFunction(UIFunction activeFunction)
{
	_impl->_activeFunction = std::move(activeFunction);
}

void UIElement::SetResizeFunction(UIFunction resizeFunction)
{
	_impl->_resizeFunction = std::move(resizeFunction);
}

void UIElement::OnLeftButtonDown(const UIEvent& e)
{
	if (_impl->_leftButtonDownFunction)
		_impl->_leftButtonDownFunction(e);
}

void UIElement::OnLeftButtonUp(const UIEvent& e)
{
	if (_impl->_leftButtonUpFunction)
		_impl->_leftButtonUpFunction(e);
}

void UIElement::OnRightButtonDown(const UIEvent& e)
{
	if (_impl->_rightButtonDownFunction)
		_impl->_rightButtonDownFunction(e);
}

void UIElement::OnRightButtonUp(const UIEvent& e)
{
	if (_impl->_rightButtonUpFunction)
		_impl->_rightButtonUpFunction(e);
}

void UIElement::OnMouseMove(const UIEvent& e)
{
	if (_impl->_mouseMoveFunction)
		_impl->_mouseMoveFunction(e);
}

void UIElement::OnMouseEnter(const UIEvent& e)
{
	if (_impl->_mouseEnterFunction)
		_impl->_mouseEnterFunction(e);
}

void UIElement::OnMouseLeave(const UIEvent& e)
{
	if (_impl->_mouseLeaveFunction)
		_impl->_mouseLeaveFunction(e);
}

void UIElement::OnActive(const UIEvent& e)
{
	if (_impl->_activeFunction)
		_impl->_activeFunction(e);
}

void UIElement::OnResize(const UIEvent& e)
{
	if (_impl->_resizeFunction)
		_impl->_resizeFunction(e);
}

void UIElement::CreateUIElementImpl(std::string_view name, UIElementPtr elem)
{
	elem->_impl->_parent = this;
	elem->_impl->_context = this->_impl->_context;
	SetAlignment(elem.get());

	try
	{
		elem->_impl->_brush = std::make_unique<SolidColorBrush>
		(
			elem->_impl->_context->GetGraphicsSystem()->GetD2DSystem()->GetD2DDevice(),
			elem->_impl->_settings.backgroundColor
		);
		if (!elem->_impl->_brush)
			throw std::runtime_error("SolidColorBrush failed to initialize.");
	}
	catch (const std::runtime_error&)
	{
		throw;
	}

	elem->OnInitialize();

	_impl->_uiChildren.emplace
	(
		std::string(name),
		std::move(elem)
	);
}

bool UIElement::DeleteUIElement(std::string_view elementName)
{
	UIElementConstIterator it = _impl->_uiChildren.find(std::string(elementName));
	if (it == _impl->_uiChildren.end())
		return false;

	_impl->_uiChildren.erase(std::string(elementName));
	return true;
}

bool UIElement::DeleteUIElement(UIElement* parent, std::string_view elementName)
{
	if (!parent)
		return false;

	return parent->DeleteUIElement(elementName);
}

UIElement* UIElement::GetUIElement(std::string_view name)
{
	std::queue<UIElement*> queue{};
	queue.push(this);

	while (!queue.empty())
	{
		const UIElement* current = queue.front();
		queue.pop();

		UIElementConstIterator it = current->_impl->_uiChildren.find(std::string(name));
		if (it != current->_impl->_uiChildren.end())
			return it->second.get();

		for (const auto& child : current->_impl->_uiChildren)
			queue.push(child.second.get());
	}

	return nullptr;
}

UIElement* UIElement::GetUIElement(UIElement* parent, std::string_view elementName)
{
	UIElementConstIterator it = parent->_impl->_uiChildren.find(std::string(elementName));
	if (it == parent->_impl->_uiChildren.end())
		return nullptr;
	return it->second.get();
}

void UIElement::SetDimension(const GraphlyMath::Vector2& dimension)
{
	_impl->_settings.dimension = dimension;
}

void UIElement::SetBackgroundColor(const Vector4& backgroundColor)
{
	_impl->_brush->SetColor(backgroundColor);
}

void UIElement::SetTranslation(const Vector2& position)
{
	_impl->_settings.transform.SetTranslation(position);
}

void UIElement::SetRotation(float angle)
{
	_impl->_settings.transform.SetRotation(angle);
}

void UIElement::SetScale(const Vector2& scale)
{
	_impl->_settings.transform.SetScale(scale);
}

void UIElement::SetTransform(const Transform& transform)
{
	_impl->_settings.transform = transform;
}

void UIElement::SetWorldTransform(const D2D1_MATRIX_3X2_F& worldTransform)
{
	_impl->_worldTransform = worldTransform;
}

const D2D1_MATRIX_3X2_F& UIElement::GetWorldTransform() const
{
	return _impl->_worldTransform;
}

const Transform& UIElement::GetTransform() const
{
	return _impl->_settings.transform;
}

const Vector4& UIElement::GetBackgroundColor() const
{
	return _impl->_brush->GetColor();
}

UIElement* UIElement::GetParent() const
{
	return _impl->_parent;
}

std::size_t UIElement::GetChildCount() const
{
	return _impl->_uiChildren.size();
}

std::size_t UIElement::GetDescendantCount()
{
	std::queue<UIElement*> queue{};
	std::size_t count = 0;
	queue.push(this);

	while (!queue.empty())
	{
		const UIElement* current = queue.front();
		count += current->_impl->_uiChildren.size();
		queue.pop();
		
		for (const auto& child : _impl->_uiChildren)
			queue.push(child.second.get());
	}

	return count;
}

bool UIElement::IsInteractable() const
{
	return _impl->_settings.isInteractable;
}

const UIElementSettings& UIElement::GetUISettings() const
{
	return _impl->_settings;
}

const std::string& UIElement::GetName() const
{
	return _impl->_name;
}

UIElement::UIElementIterator UIElement::begin()
{
	return _impl->_uiChildren.begin();
}

UIElement::UIElementConstIterator UIElement::begin() const
{
	return _impl->_uiChildren.begin();
}

UIElement::UIElementIterator UIElement::UIElement::end()
{
	return _impl->_uiChildren.end();
}

UIElement::UIElementConstIterator UIElement::end() const
{
	return _impl->_uiChildren.end();
}
