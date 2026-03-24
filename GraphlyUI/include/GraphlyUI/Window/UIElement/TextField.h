#ifndef GRAPHLYUI_TEXTFIELD_HEADER
#define GRAPHLYUI_TEXTFIELD_HEADER

#include "UIElement.h"

namespace GraphlyUI
{
	struct GRAPHLYUI_API TextFieldSettings : public UIElementSettings
	{
		TextFieldSettings()
		: UIElementSettings(UIElementType::TextField) {}
	};

	class GRAPHLYUI_API TextField final : public UIElement
	{
	public:
		TextField(std::string_view name, const UIElementSettings& uiElemSettings, const TextFieldSettings& textFieldSettings);
		TextField(std::string_view name, UIElementSettings&& uiElemSettings, TextFieldSettings&& textFieldSettings);
		TextField(const TextField& other) = delete;
		TextField(TextField&& other) = delete;
		~TextField() = default;

		TextField& operator = (const TextField& other) = delete;
		TextField& operator = (TextField&& other) = delete;

	private:
		TextFieldSettings _settings{};
	};

	using TextFieldPtr       = std::unique_ptr<TextField>;
	using TextFieldSharedPtr = std::shared_ptr<TextField>;
}

#endif // GRAPHLYUI_TEXTFIELD_HEADER
