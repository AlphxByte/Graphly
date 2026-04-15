#include "TextImpl.h"
#include "UIElementImpl.h"
#include "../UIContext.h"
#include "../../GraphicsSystem/GraphicsSystem.h"

using namespace GraphlyUI;

Text::Text(std::string_view name, const TextElementSettings& textElementSettings)
: UIElement(name, textElementSettings.ui)
{
	_impl = std::make_unique<TextImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("Text failed to initialize.");

	_impl->_settings = textElementSettings.textSettings;
}

Text::Text(std::string_view name, TextElementSettings&& textElementSettings)
: UIElement(name, std::move(textElementSettings.ui))
{
	_impl = std::make_unique<TextImpl>();
	[[unlikely]] if (!_impl)
		throw std::runtime_error("Text failed to initialize.");

	_impl->_settings = std::move(textElementSettings.textSettings);
}

Text::~Text()
{

}

void Text::Render()
{
	if (_impl->_settings.renderBackground)
		UIElement::Render();

	// Use local space
	UIElement::_impl->_context
	->GetGraphicsSystem()
	->GetD2DSystem()
	->GetD2DDevice()
	->GetContext()
	->DrawTextLayout
	(
		D2D1::Point2F(0.0f, 0.0f),
		_impl->_textLayout.Get(),
		_impl->_textBrush.get()->GetBrush()
	);
}

void Text::OnInitialize()
{
	// Use the impl from UIElement not from Text to get the text format
	_impl->_textFormat = UIElement::_impl->_context
						->GetGraphicsSystem()
						->GetTextSystem()
						->GetTextFormat(_impl->_settings.textFormatName);
 
	auto writeFactory = UIElement::_impl->_context
						->GetGraphicsSystem()
						->GetTextSystem()
						->GetWriteFactory()
						->GetFactory();

	// Create text brush
	try
	{
		_impl->_textBrush = std::make_unique<SolidColorBrush>
		(
			UIElement::_impl->_context->GetGraphicsSystem()->GetD2DSystem()->GetD2DDevice(),
			_impl->_settings.textColor
		);
		if (!_impl->_textBrush)
			throw std::runtime_error("Text initialization failed.");
	}
	catch (const std::runtime_error&)
	{
		throw;
	}

	// Create text layout
	HRESULT result = writeFactory->CreateTextLayout
	(
		_impl->_settings.str.c_str(),
		(UINT32) _impl->_settings.str.length(),
		_impl->_textFormat->GetTextFormat(),
		UIElement::_impl->_settings.dimension.GetX(),
		UIElement::_impl->_settings.dimension.GetY(),
		&_impl->_textLayout
	);
	if (FAILED(result))
		throw std::runtime_error("Text failed to initialize.");

	// Create ellipsis trimming
	result = writeFactory->CreateEllipsisTrimmingSign
	(
		_impl->_textFormat->GetTextFormat(),
		&_impl->_ellipsis
	);
	if (FAILED(result))
		throw std::runtime_error("Text failed to initialize.");

	SetTextAlignment(_impl->_settings.textLayoutSettings.textAlignment);
	SetParagraphAlignment(_impl->_settings.textLayoutSettings.paragraphAlignment);
	SetWordWrapping(_impl->_settings.textLayoutSettings.wordWrapping);
	SetTextTrimming(_impl->_settings.textLayoutSettings.textTrimming);
}

void Text::SetTextAlignment(const TextAlignment& textAlignment)
{
	_impl->_settings.textLayoutSettings.textAlignment = textAlignment;

	HRESULT result = _impl->_textLayout->SetTextAlignment
	(
		_impl->GetTextAlignment(textAlignment)
	);
	if (FAILED(result))
		throw std::runtime_error("Text failed to initialize.");
}

void Text::SetParagraphAlignment(const ParagraphAlignment& paragraphAlignment)
{
	_impl->_settings.textLayoutSettings.paragraphAlignment = paragraphAlignment;

	HRESULT result = _impl->_textLayout->SetParagraphAlignment
	(
		_impl->GetParagraphAlignment(paragraphAlignment)
	);
	if (FAILED(result))
		throw std::runtime_error("Text failed to initialize.");
}

void Text::SetWordWrapping(const WordWrapping& wordWrapping)
{
	_impl->_settings.textLayoutSettings.wordWrapping = wordWrapping;

	HRESULT result = _impl->_textLayout->SetWordWrapping
	(
		_impl->GetWordWrapping(wordWrapping)
	);
	if (FAILED(result))
		throw std::runtime_error("Text failed to initialize.");
}

void Text::SetTextTrimming(const TextTrimming& textTrimming)
{
	_impl->_settings.textLayoutSettings.textTrimming = textTrimming;

	DWRITE_TRIMMING trimming{};
	trimming.granularity = _impl->GetTrimmingGranularity(textTrimming);
	HRESULT result = _impl->_textLayout->SetTrimming
	(
		&trimming,
		_impl->_ellipsis.Get()
	);
	if (FAILED(result))
		throw std::runtime_error("Text failed to initialize.");
}

const TextSettings& Text::GetTextSettings() const
{
	return _impl->_settings;
}

const DWRITE_TEXT_ALIGNMENT Text::TextImpl::GetTextAlignment(const TextAlignment& alignment)
{
	switch (alignment)
	{
	default:
	case TextAlignment::Leading:
		return DWRITE_TEXT_ALIGNMENT_LEADING;
	case TextAlignment::Trailing:
		return DWRITE_TEXT_ALIGNMENT_TRAILING;
	case TextAlignment::Center:
		return DWRITE_TEXT_ALIGNMENT_CENTER;
	case TextAlignment::Justified:
		return DWRITE_TEXT_ALIGNMENT_JUSTIFIED;
	}
}

const DWRITE_PARAGRAPH_ALIGNMENT Text::TextImpl::GetParagraphAlignment(const ParagraphAlignment& alignment)
{
	switch (alignment)
	{
	default:
	case ParagraphAlignment::Near:
		return DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
	case ParagraphAlignment::Center:
		return DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	case ParagraphAlignment::Far:
		return DWRITE_PARAGRAPH_ALIGNMENT_FAR;
	}
}

const DWRITE_WORD_WRAPPING Text::TextImpl::GetWordWrapping(const WordWrapping& wrapping)
{
	switch (wrapping)
	{
	default:
	case WordWrapping::Wrap:
		return DWRITE_WORD_WRAPPING_WRAP;
	case WordWrapping::NoWrap:
		return DWRITE_WORD_WRAPPING_NO_WRAP;
	case WordWrapping::EmergencyBreak:
		return DWRITE_WORD_WRAPPING_EMERGENCY_BREAK;
	case WordWrapping::WholeWord:
		return DWRITE_WORD_WRAPPING_WHOLE_WORD;
	case WordWrapping::Character:
		return DWRITE_WORD_WRAPPING_CHARACTER;
	}
}

const DWRITE_TRIMMING_GRANULARITY Text::TextImpl::GetTrimmingGranularity(const TextTrimming& trimming)
{
	switch (trimming)
	{
	case TextTrimming::None:
		return DWRITE_TRIMMING_GRANULARITY_NONE;
	default:
	case TextTrimming::Character:
		return DWRITE_TRIMMING_GRANULARITY_CHARACTER;
	case TextTrimming::Word:
		return DWRITE_TRIMMING_GRANULARITY_WORD;
	}
}
