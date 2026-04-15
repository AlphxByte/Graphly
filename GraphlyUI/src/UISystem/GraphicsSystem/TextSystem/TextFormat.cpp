#include "TextFormat.h"
#include "WriteFactory.h"
#include "GraphlyUI/UISystem/Window/UIElement/TextFormatSettings.h"

#include <stdexcept>

using namespace GraphlyUI;

TextFormat::TextFormat(WriteFactory* factory, const TextFormatSettings& settings)
: _factory(factory), _settings(settings)
{
	if (!Initialize())
		throw std::runtime_error("TextFormat failed to initialize.");
}

TextFormat::TextFormat(WriteFactory* factory, TextFormatSettings&& settings)
: _factory(factory), _settings(std::move(settings))
{
	if (!Initialize())
		throw std::runtime_error("TextFormat failed to initialize.");
}

bool TextFormat::Initialize()
{
	HRESULT result = _factory->GetFactory()->CreateTextFormat
	(
		_settings.fontFamily.c_str(),
		nullptr,
		GetFontWeight(_settings.fontWeight),
		GetFontStyle(_settings.fontStyle),
		GetFontStretch(_settings.fontStretch),
		_settings.fontSize,
		GetLocaleName(_settings.fontLanguage),
		&_textFormat
	);
	if (FAILED(result))
		return false;

	return true;
}

IDWriteTextFormat* TextFormat::GetTextFormat() const
{
	return _textFormat.Get();
}

const TextFormatSettings& TextFormat::GetSettings() const
{
	return _settings;
}

const DWRITE_FONT_WEIGHT TextFormat::GetFontWeight(FontWeight fontWeight) const
{
	switch (fontWeight)
	{
	case FontWeight::Thin:
		return DWRITE_FONT_WEIGHT_THIN;
	case FontWeight::Light:
		return DWRITE_FONT_WEIGHT_LIGHT;
	default:
	case FontWeight::Normal:
		return DWRITE_FONT_WEIGHT_NORMAL;
	case FontWeight::Semibold:
		return DWRITE_FONT_WEIGHT_SEMI_BOLD;
	case FontWeight::Bold:
		return DWRITE_FONT_WEIGHT_BOLD;
	case FontWeight::Black:
		return DWRITE_FONT_WEIGHT_BLACK;
	}
}

const DWRITE_FONT_STYLE TextFormat::GetFontStyle(FontStyle fontStyle) const
{
	switch (fontStyle)
	{
	default:
	case FontStyle::Normal:
		return DWRITE_FONT_STYLE_NORMAL;
	case FontStyle::Oblique:
		return DWRITE_FONT_STYLE_OBLIQUE;
	case FontStyle::Italic:
		return DWRITE_FONT_STYLE_ITALIC;
	}
}

const DWRITE_FONT_STRETCH TextFormat::GetFontStretch(FontStretch fontStretch) const
{
	switch (fontStretch)
	{
	case FontStretch::UltraCondensed:
		return DWRITE_FONT_STRETCH_ULTRA_CONDENSED;
	case FontStretch::Condensed:
		return DWRITE_FONT_STRETCH_CONDENSED;
	default:
	case FontStretch::Normal:
		return DWRITE_FONT_STRETCH_NORMAL;
	case FontStretch::Expanded:
		return DWRITE_FONT_STRETCH_EXPANDED;
	case FontStretch::ExtraExpanded:
		return DWRITE_FONT_STRETCH_EXTRA_EXPANDED;
	}
}

const WCHAR* TextFormat::GetLocaleName(FontLanguage fontLanguage) const
{
	switch (fontLanguage)
	{
	default:
	case FontLanguage::EnUS:
		return L"en-us";
	case FontLanguage::EnGB:
		return L"en-gb";
	case FontLanguage::EnAU:
		return L"en-au";
	case FontLanguage::EnCA:
		return L"en-ca";
	case FontLanguage::De:
		return L"de-de";
	case FontLanguage::Fr:
		return L"fr-fr";
	case FontLanguage::Es:
		return L"es-es";
	case FontLanguage::EsMX:
		return L"es-mx";
	case FontLanguage::It:
		return L"it-it";
	case FontLanguage::Pt:
		return L"pt-pt";
	case FontLanguage::PtBR:
		return L"pt-br";
	case FontLanguage::Nl:
		return L"nl-nl";
	case FontLanguage::SvSE:
		return L"sv-se";
	case FontLanguage::DaDK:
		return L"da-dk";
	case FontLanguage::Fi:
		return L"fi-fi";
	case FontLanguage::No:
		return L"no-no";
	case FontLanguage::Pl:
		return L"pl-pl";
	case FontLanguage::Ru:
		return L"ru-ru";
	case FontLanguage::UkUA:
		return L"uk-ua";
	case FontLanguage::Bg:
		return L"bg-bg";
	case FontLanguage::CsCZ:
		return L"cs-cz";
	case FontLanguage::Sk:
		return L"sk-sk";
	case FontLanguage::Ro:
		return L"ro-ro";
	case FontLanguage::JaJP:
		return L"ja-jp";
	case FontLanguage::KoKR:
		return L"ko-kr";
	case FontLanguage::ZhCN:
		return L"zh-cn";
	case FontLanguage::ZhTW:
		return L"zh-tw";
	case FontLanguage::ZhHK:
		return L"zh-hk";
	case FontLanguage::ArSA:
		return L"ar-sa";
	case FontLanguage::ArEg:
		return L"ar-eg";
	case FontLanguage::HeIL:
		return L"he-il";
	case FontLanguage::FaIR:
		return L"fa-ir";
	case FontLanguage::HiIN:
		return L"hi-in";
	case FontLanguage::BnIN:
		return L"bn-in";
	case FontLanguage::TaIN:
		return L"ta-in";
	}
}
