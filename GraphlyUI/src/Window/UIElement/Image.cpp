#include "GraphlyUI/Window/UIElement/Image.h"

using namespace GraphlyUI;

Image::Image(std::string_view name, const UIElementSettings& uiElemSettings, const ImageSettings& imageSettings)
: UIElement(name, uiElemSettings), _settings(imageSettings)
{

}

Image::Image(std::string_view name, UIElementSettings&& uiElemSettings, ImageSettings&& imageSettings)
: UIElement(name, std::forward<UIElementSettings>(uiElemSettings)), 
_settings(std::forward<ImageSettings>(imageSettings))
{

}
