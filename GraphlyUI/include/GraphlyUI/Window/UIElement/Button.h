#ifndef GRAPHLYUI_BUTTON_HEADER
#define GRAPHLYUI_BUTTON_HEADER

#include "UIElement.h"

namespace GraphlyUI
{
	struct GRAPHLYUI_API ButtonSettings : public UIElementSettings
	{
		ButtonSettings()
		: UIElementSettings(UIElementType::Button)
		{}
	};

	class GRAPHLYUI_API Button final : public UIElement
	{
	public:
		Button(std::string_view name, const UIElementSettings& uiElemSettings, const ButtonSettings& buttonSettings);
		Button(std::string_view name, UIElementSettings&& uiElemSettings, ButtonSettings&& buttonSettings);
		Button(const Button& other) = delete;
		Button(Button&& other) = delete;
		~Button() = default;

		Button& operator = (const Button& other) = delete;
		Button& operator = (Button&& other) = delete;

	private:
		ButtonSettings _settings{};
	};

	using ButtonPtr       = std::unique_ptr<Button>;
	using ButtonSharedPtr = std::shared_ptr<Button>;
}

#endif // GRAPHLYUI_BUTTON_HEADER
