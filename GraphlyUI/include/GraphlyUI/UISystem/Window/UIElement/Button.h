#ifndef GRAPHLYUI_BUTTON_HEADER
#define GRAPHLYUI_BUTTON_HEADER

#include "UIElement.h"
#include "Text.h"

namespace GraphlyUI
{
	struct GRAPHLYUI_API ButtonSettings
	{
		TextSettings textSettings{};
		GraphlyMath::Transform textTransform;
	};

	struct GRAPHLYUI_API ButtonElementSettings final
	{
		UIElementSettings ui{};
		ButtonSettings buttonSettings{};
	};

	class GRAPHLYUI_API Button : public UIElement
	{
	public:
		Button(std::string_view name, const ButtonElementSettings& buttonElementSettings);
		Button(std::string_view name, ButtonElementSettings&& buttonElementSettings);
		Button(const Button& other) = delete;
		Button(Button&& other) = delete;
		~Button();

		void Render() override;

		[[nodiscard]] Text* GetText();
		[[nodiscard]] const ButtonSettings& GetButtonSettings() const;

		Button& operator = (const Button& other) = delete;
		Button& operator = (Button&& other) = delete;

	private:
		void OnInitialize() override;

		struct ButtonImpl;
		std::unique_ptr<ButtonImpl> _impl{};
	};

	using ButtonPtr       = std::unique_ptr<Button>;
	using ButtonSharedPtr = std::shared_ptr<Button>;
}

#endif // GRAPHLYUI_BUTTON_HEADER
