#ifndef GRAPHLYUI_TEXTIMPL_HEADER
#define GRAPHLYUI_TEXTIMPL_HEADER

#include "GraphlyUI/UISystem/Window/UIElement/Text.h"
#include "../../GraphicsSystem/D2DSystem/SolidColorBrush.h"

#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <dwrite_3.h>
#include <wrl.h>

namespace GraphlyUI
{
	class TextFormat;

	struct Text::TextImpl final
	{
		TextImpl() = default;
		TextImpl(const TextImpl& other) = delete;
		TextImpl(TextImpl&& other) = delete;
		~TextImpl() = default;

		[[nodiscard]] const DWRITE_TEXT_ALIGNMENT GetTextAlignment(const TextAlignment& alignment);
		[[nodiscard]] const DWRITE_PARAGRAPH_ALIGNMENT GetParagraphAlignment(const ParagraphAlignment& alignment);
		[[nodiscard]] const DWRITE_WORD_WRAPPING GetWordWrapping(const WordWrapping& wrapping);
		[[nodiscard]] const DWRITE_TRIMMING_GRANULARITY GetTrimmingGranularity(const TextTrimming& trimming);

		TextImpl& operator = (const TextImpl& other) = delete;
		TextImpl& operator = (TextImpl&& other) = delete;

		// Members section
		TextSettings _settings{};

		Microsoft::WRL::ComPtr<IDWriteTextLayout> _textLayout{};
		Microsoft::WRL::ComPtr<IDWriteInlineObject> _ellipsis{};
		SolidColorBrushPtr _textBrush{};

		// Not owned resources
		TextFormat* _textFormat{};
	};
}

#endif // GRAPHLYUI_TEXTIMPL_HEADER
