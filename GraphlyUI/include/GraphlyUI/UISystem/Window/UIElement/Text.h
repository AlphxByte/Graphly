#ifndef GRAPHLYUI_TEXT_HEADER
#define GRAPHLYUI_TEXT_HEADER

#include "TextFormatSettings.h"
#include "TextLayoutSettings.h"
#include "UIElement.h"

namespace GraphlyUI
{
	struct GRAPHLYUI_API TextSettings
	{
		TextLayoutSettings textLayoutSettings{};
		std::wstring str{};
		std::string textFormatName;
		GraphlyMath::Vector4 textColor{ 0.0f, 0.0f, 0.0f, 1.0f };
		bool renderBackground = true;
	};

	struct GRAPHLYUI_API TextElementSettings final
	{
		UIElementSettings ui{};
		TextSettings textSettings{};
	};

	class GRAPHLYUI_API Text : public UIElement
	{
	public:
		Text(std::string_view name, const TextElementSettings& textElementSettings);
		Text(std::string_view name, TextElementSettings&& textElementSettings);
		Text(const Text& other) = delete;
		Text(Text&& other) = delete;
		virtual ~Text();

		void Render() override;

		void SetTextAlignment(const TextAlignment& textAlignment);
		void SetParagraphAlignment(const ParagraphAlignment& paragraphAlignment);
		void SetWordWrapping(const WordWrapping& wordWrapping);
		void SetTextTrimming(const TextTrimming& textTrimming);

		[[nodiscard]] const TextSettings& GetTextSettings() const;

		Text& operator = (const Text& other) = delete;
		Text& operator = (Text&& other) = delete;

	private:
		void OnInitialize() override;

		struct TextImpl;
		std::unique_ptr<TextImpl> _impl{};
	};

	using TextPtr       = std::unique_ptr<Text>;
	using TextSharedPtr = std::shared_ptr<Text>;
}

#endif // GRAPHLYUI_TEXT_HEADER
