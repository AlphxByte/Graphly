#include "WindowFactory.h"
#include "GraphicsSystem/GraphicsSystem.h"
#include "GraphlyUI/UISystem/Window/Window.h"

using namespace GraphlyUI;

WindowPtr WindowFactory::CreateWindowFromSettings(const WindowSettings& settings)
{
	return std::make_unique<Window>(settings);
}

WindowPtr WindowFactory::CreateWindowFromSettings(WindowSettings&& settings)
{
	return std::make_unique<Window>(std::move(settings));
}
