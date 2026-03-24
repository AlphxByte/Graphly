#include "GraphlyUI/Window/UIElement/TextField.h"

using namespace GraphlyUI;

TextField::TextField(std::string_view name, const UIElementSettings& uiElemSettings, const TextFieldSettings& textFieldSettings)
: UIElement(name, uiElemSettings), _settings(textFieldSettings)
{

}

TextField::TextField(std::string_view name, UIElementSettings&& uiElemSettings, TextFieldSettings&& textFieldSettings)
: UIElement(name, std::forward<UIElementSettings>(uiElemSettings)), 
_settings(std::forward<TextFieldSettings>(textFieldSettings))
{

}
