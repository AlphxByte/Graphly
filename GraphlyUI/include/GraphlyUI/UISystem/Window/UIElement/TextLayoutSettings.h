#ifndef GRAPHLYUI_TEXT_LAYOUT_HEADER
#define GRAPHLYUI_TEXT_LAYOUT_HEADER

#include "../../../GraphlyUIExports.h"

namespace GraphlyUI
{
	enum class TextAlignment
	{
		Leading,
		Trailing,
		Center,
		Justified
	};

	enum class ParagraphAlignment
	{
		Near,
		Center,
		Far
	};

	enum class WordWrapping
	{
		Wrap,
		NoWrap,
		EmergencyBreak,
		WholeWord,
		Character
	};

	enum class TextTrimming
	{
		None,
		Character,
		Word
	};

	struct GRAPHLYUI_API TextLayoutSettings final
	{
		TextAlignment textAlignment = TextAlignment::Leading;
		ParagraphAlignment paragraphAlignment = ParagraphAlignment::Near;
		WordWrapping wordWrapping = WordWrapping::Wrap;
		TextTrimming textTrimming = TextTrimming::Character;
	};
}

#endif // GRAPHLYUI_TEXT_LAYOUT_HEADER
