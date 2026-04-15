#ifndef GRAPHLYUI_BUTTON_IMPL_HEADER
#define GRAPHLYUI_BUTTON_IMPL_HEADER

#include "GraphlyUI/UISystem/Window/UIElement/Button.h"
#include "GraphlyUI/UISystem/Window/UIElement/Text.h"

namespace GraphlyUI
{
	struct Button::ButtonImpl
	{
		ButtonImpl() = default;
		ButtonImpl(const ButtonImpl& other) = delete;
		ButtonImpl(ButtonImpl&& other) = delete;
		~ButtonImpl() = default;

		ButtonImpl& operator = (const ButtonImpl& other) = delete;
		ButtonImpl& operator = (ButtonImpl&& other) = delete;

		// Members section
		ButtonSettings _settings{};

		// Not owned (owned by the map _uiChildren)
		Text* _text{};
	};
}

#endif // GRAPHLYUI_BUTTON_IMPL_HEADER
