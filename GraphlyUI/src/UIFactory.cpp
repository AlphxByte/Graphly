#include "UIFactory.h"

using namespace GraphlyUI;

UIFactory::UIFactory(HWND hwnd)
: _hwnd(hwnd)
{

}

UIElementPtr UIFactory::CreateUIElement(std::string_view name, const UIElementSettings& settings)
{
	return std::make_unique<UIElement>(name, settings);
}

UIElementPtr UIFactory::CreateUIElement(std::string_view name, UIElementSettings&& settings)
{
	return std::make_unique<UIElement>(name, std::forward<UIElementSettings>(settings));
}

HWND GraphlyUI::UIFactory::GetHWND() const
{
	return _hwnd;
}
