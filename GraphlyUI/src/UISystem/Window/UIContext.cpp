#include "UIContext.h"
#include "../GraphicsSystem/GraphicsSystem.h"

using namespace GraphlyUI;

void UIContext::SetGraphicsSystem(GraphicsSystem* graphicsSystem)
{
	_graphicsSystem = graphicsSystem;
}

void UIContext::SetUIFactory(UIFactory* uiFactory)
{
	_uiFactory = uiFactory;
}

GraphicsSystem* UIContext::GetGraphicsSystem()
{
	return _graphicsSystem;
}

UIFactory* UIContext::GetUIFactory() const
{
	return _uiFactory;
}
