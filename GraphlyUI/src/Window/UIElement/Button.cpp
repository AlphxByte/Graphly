#include "GraphlyUI/Window/UIElement/Button.h"

using namespace GraphlyUI;

Button::Button(std::string_view name, const UIElementSettings& uiElemSettings, const ButtonSettings& buttonSettings)
: UIElement(name, uiElemSettings), _settings(buttonSettings)
{

}

Button::Button(std::string_view name, UIElementSettings&& uiElemSettings, ButtonSettings&& buttonSettings)
: UIElement(name, std::forward<UIElementSettings>(uiElemSettings)),
_settings(std::forward<ButtonSettings>(buttonSettings))
{

}
