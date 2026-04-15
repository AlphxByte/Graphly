#ifndef GRAPHLYUI_TEXT_FORMAT_SETTINGS_HEADER
#define GRAPHLYUI_TEXT_FORMAT_SETTINGS_HEADER

#include "../../../GraphlyUIExports.h"

#include <string>
#include <optional>

namespace GraphlyUI
{
	enum class FontWeight
	{
		Thin,
		Light,
		Normal,
		Semibold,
		Bold,
		Black
	};

	enum class FontStyle
	{
		Normal,
		Oblique,
		Italic
	};

	enum class FontStretch
	{
		UltraCondensed,
		Condensed,
		Normal,
		Expanded,
		ExtraExpanded
	};

	enum class FontLanguage
	{
		EnUS,
		EnGB,
		EnAU,
		EnCA,
		De,
		Fr,
		Es,
		EsMX,
		It,
		Pt,
		PtBR,
		Nl,
		SvSE,
		DaDK,
		Fi,
		No,
		Pl,
		Ru,
		UkUA,
		Bg,
		CsCZ,
		Sk,
		Ro,
		JaJP,
		KoKR,
		ZhCN,
		ZhTW,
		ZhHK,
		ArSA,
		ArEg,
		HeIL,
		FaIR,
		HiIN,
		BnIN,
		TaIN
	};

	struct GRAPHLYUI_API TextFormatSettings final
	{
		std::wstring fontFamily = L"Segoe UI";
		FontWeight fontWeight = FontWeight::Normal;
		FontStyle fontStyle = FontStyle::Normal;
		FontStretch fontStretch = FontStretch::Normal;
		float fontSize = 12.0f;
		FontLanguage fontLanguage = FontLanguage::EnUS;
	};
}

#endif // GRAPHLYUI_TEXT_FORMAT_SETTINGS_HEADER