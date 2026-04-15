#ifndef GRAPHLYUI_TEXT_FORMAT_HEADER
#define GRAPHLYUI_TEXT_FORMAT_HEADER

#include "GraphlyUI/UISystem/Window/UIElement/TextFormatSettings.h"

#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <dwrite_3.h>
#include <wrl.h>
#include <memory>

namespace GraphlyUI
{
	class WriteFactory;

	class TextFormat final
	{
	public:
		TextFormat(WriteFactory* factory, const TextFormatSettings& settings);
		TextFormat(WriteFactory* factory, TextFormatSettings&& settings);
		TextFormat(const TextFormat& other) = delete;
		TextFormat(TextFormat&& other) = delete;
		~TextFormat() = default;

		[[nodiscard]] IDWriteTextFormat* GetTextFormat() const;
		[[nodiscard]] const TextFormatSettings& GetSettings() const;

		TextFormat& operator = (const TextFormat& other) = delete;
		TextFormat& operator = (TextFormat&& other) = delete;

	private:
		[[nodiscard]] bool Initialize();
		[[nodiscard]] const DWRITE_FONT_WEIGHT GetFontWeight(FontWeight fontWeight) const;
		[[nodiscard]] const DWRITE_FONT_STYLE GetFontStyle(FontStyle fontStyle) const;
		[[nodiscard]] const DWRITE_FONT_STRETCH GetFontStretch(FontStretch fontStretch) const;
		[[nodiscard]] const WCHAR* GetLocaleName(FontLanguage fontLanguage) const;

	private:
		TextFormatSettings _settings{};

		Microsoft::WRL::ComPtr<IDWriteTextFormat> _textFormat{};

		// Not owned resources
		WriteFactory* _factory{};
	};

	using TextFormatPtr = std::unique_ptr<TextFormat>;
	using TextFormatSharedPtr = std::shared_ptr<TextFormat>;
}

#endif // GRAPHLYUI_TEXT_FORMAT_HEADER
