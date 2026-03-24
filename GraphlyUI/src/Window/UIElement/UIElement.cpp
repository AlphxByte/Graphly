#include "GraphlyUI/Window/UIElement/UIElement.h"
#include "../UIContext/UIFactory/UIFactory.h"

#include <queue>
#include <stdexcept>

using namespace GraphlyUI;

UIElement::UIElement(std::string_view name, const UIElementSettings& settings)
: _settings(settings), _factory(_settings.parent->_factory), _name(std::string(name))
{
	[[unlikely]] if (!Initialize())
		throw std::runtime_error("UIElement initialization failed.");
}

UIElement::UIElement(std::string_view name, UIElementSettings&& settings)
: _settings(std::forward<UIElementSettings>(settings)), _factory(_settings.parent->_factory),
_name(std::string(name))
{
	[[unlikely]] if (!Initialize())
		throw std::runtime_error("UIElement initialization failed.");
}

// Root constructors
UIElement::UIElement(UIFactory* factory, std::string_view name, const UIElementSettings& settings)
: _settings(settings), _factory(factory), _name(std::string(name))
{
	_parent = nullptr;
	[[unlikely]] if (!Initialize())
		throw std::runtime_error("UIElement initialization failed.");
}

UIElement::UIElement(UIFactory* factory, std::string_view name, UIElementSettings&& settings)
: _settings(std::forward<UIElementSettings>(settings)), _factory(factory), _name(std::string(name))
{
	_parent = nullptr;
	[[unlikely]] if (!Initialize())
		throw std::runtime_error("UIElement initialization failed.");
}

bool UIElement::Initialize()
{
	return true;
}

UIElement* UIElement::AddUIElement(std::string_view name, const UIElementSettings& settings)
{
	return _uiChildren.emplace
	(
		std::string(name), 
		_factory->CreateUIElement(name, settings)
	).first->second.get();
}

UIElement* UIElement::AddUIElement(std::string_view name, UIElementSettings&& settings)
{
	return _uiChildren.emplace
	(
		std::string(name),
		_factory->CreateUIElement(name, std::forward<UIElementSettings>(settings))
	).first->second.get();
}

bool UIElement::DeleteUIElement(std::string_view elementName)
{
	UIElementConstIterator it = _uiChildren.find(std::string(elementName));
	if (it == _uiChildren.end())
		return false;

	_uiChildren.erase(std::string(elementName));
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

		UIElementConstIterator it = current->_uiChildren.find(std::string(name));
		if (it != current->_uiChildren.end())
			return it->second.get();

		for (const auto& child : current->_uiChildren)
			queue.push(child.second.get());
	}

	return nullptr;
}

UIElement* UIElement::GetUIElement(UIElement* parent, std::string_view elementName)
{
	UIElementConstIterator it = parent->_uiChildren.find(std::string(elementName));
	if (it == parent->_uiChildren.end())
		return nullptr;
	return it->second.get();
}

UIElement* UIElement::GetParent() const
{
	return _parent;
}

std::size_t UIElement::GetChildCount() const
{
	return _uiChildren.size();
}

std::size_t UIElement::GetDescendantCount()
{
	std::queue<UIElement*> queue{};
	std::size_t count = 0;
	queue.push(this);

	while (!queue.empty())
	{
		const UIElement* current = queue.front();
		count += current->_uiChildren.size();
		queue.pop();
		
		for (const auto& child : _uiChildren)
			queue.push(child.second.get());
	}

	return count;
}
