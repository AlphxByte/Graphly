#include "ButtonImpl.h"
#include "UIElementImpl.h"

#include "GraphlyMath/GraphlyMath.h"

using namespace GraphlyUI;
using namespace GraphlyMath;

Button::Button(std::string_view name, const ButtonElementSettings& buttonElementSettings)
: UIElement(name, buttonElementSettings.ui)
{
	_impl = std::make_unique<ButtonImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("Button failed to initialize.");

	_impl->_settings = buttonElementSettings.buttonSettings;
}

Button::Button(std::string_view name, ButtonElementSettings&& buttonElementSettings)
: UIElement(name, std::move(buttonElementSettings.ui))
{
	_impl = std::make_unique<ButtonImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("Button failed to initialize.");

	_impl->_settings = std::move(buttonElementSettings.buttonSettings);
}

void Button::OnInitialize()
{
	try
	{
		TextElementSettings textElementSettings{};
		textElementSettings.textSettings = _impl->_settings.textSettings;
		textElementSettings.textSettings.renderBackground = false;
		textElementSettings.ui.isInteractable = false;
		textElementSettings.ui.transform = _impl->_settings.textTransform;
		textElementSettings.ui.alignment = UIElementAlignment::Center;
		textElementSettings.ui.backgroundColor = UIElement::_impl->_settings.backgroundColor;
		textElementSettings.ui.dimension = UIElement::_impl->_settings.dimension;

		_impl->_text = this->CreateUIElement<Text>("button text", textElementSettings);
		if (!_impl->_text)
			throw std::runtime_error("Button failed to initialize.");
	}
	catch (const std::runtime_error&)
	{
		throw;
	}
}

Button::~Button()
{

}

void Button::Render()
{
	UIElement::Render();
	_impl->_text->Render();
}

Text* Button::GetText()
{
	return _impl->_text;
}

const ButtonSettings& Button::GetButtonSettings() const
{
	return _impl->_settings;
}
