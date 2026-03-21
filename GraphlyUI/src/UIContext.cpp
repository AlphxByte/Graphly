#include "UIContext.h"

using namespace GraphlyUI;

UIContext::UIContext(HWND hwnd)
: _hwnd(hwnd)
{
	_factory = std::make_unique<UIFactory>(hwnd);
	[[unlikely]] if (!_factory)
		throw std::runtime_error("Factory initialization failed.");

	// TODO create root element
}

UIElement* UIContext::GetRoot() const
{
	if (_root)
		return _root.get();
	return nullptr;
}
