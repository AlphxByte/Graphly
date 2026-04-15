#include "RectangleImpl.h"

#include <stdexcept>

using namespace GraphlyUI;

Rectangle::Rectangle(std::string_view name, const UIElementSettings& settings)
: UIElement(name, settings)
{
	_impl = std::make_unique<RectangleImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("Rectangle failed to initialize.");

	if (!_impl->Initialize())
		throw std::runtime_error("Rectangle failed to initialize.");
}

Rectangle::Rectangle(std::string_view name, UIElementSettings&& settings)
: UIElement(name, std::move(settings))
{
	_impl = std::make_unique<RectangleImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("Rectangle failed to initialize.");

	if (!_impl->Initialize())
		throw std::runtime_error("Rectangle failed to initialize.");
}

// Constructors for root element
Rectangle::Rectangle(UIContext* context, std::string_view name, const UIElementSettings& settings)
: UIElement(context, name, settings)
{ 
	_impl = std::make_unique<RectangleImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("Rectangle failed to initialize.");

	if (!_impl->Initialize())
		throw std::runtime_error("Rectangle failed to initialize.");
}

Rectangle::Rectangle(UIContext* context, std::string_view name, UIElementSettings&& settings)
: UIElement(context, name, std::move(settings))
{
	_impl = std::make_unique<RectangleImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("Rectangle failed to initialize.");

	if (!_impl->Initialize())
		throw std::runtime_error("Rectangle failed to initialize.");
}

Rectangle::~Rectangle()
{

}

bool Rectangle::RectangleImpl::Initialize()
{
	return true;
}

void Rectangle::OnInitialize()
{

}

void Rectangle::Render()
{
	UIElement::Render();
}
