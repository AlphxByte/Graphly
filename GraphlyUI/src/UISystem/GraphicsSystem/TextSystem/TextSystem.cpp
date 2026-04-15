#include "TextSystem.h"

#include <stdexcept>

using namespace GraphlyUI;

TextSystem::TextSystem()
{
	if (!Initialize())
		throw std::runtime_error("TextSystem failed to initialize.");
}

bool TextSystem::Initialize()
{
	// WriteFactory section
	try
	{
		_writeFactory = std::make_unique<WriteFactory>();
		if (!_writeFactory)
			return false;
	}
	catch (const std::runtime_error&)
	{
		return false;
	}

	return true;
}

TextFormat* TextSystem::CreateTextFormat(std::string_view name, const TextFormatSettings& settings)
{
	TextFormatIterator it = _textFormats.find(std::string(name));
	if (it != _textFormats.end())
		return it->second.get();

	return _textFormats.emplace
	(
		std::string(name), 
		std::make_unique<TextFormat>
		(
			_writeFactory.get(), 
		settings
		)
	).first->second.get();
}

TextFormat* TextSystem::CreateTextFormat(std::string_view name, TextFormatSettings&& settings)
{
	TextFormatIterator it = _textFormats.find(std::string(name));
	if (it != _textFormats.end())
		return it->second.get();

	return _textFormats.emplace
	(
		std::string(name),
		std::make_unique<TextFormat>
		(
			_writeFactory.get(),
			std::move(settings)
		)
	).first->second.get();
}

bool TextSystem::DestroyTextFormat(std::string_view name)
{
	TextFormatIterator it = _textFormats.find(std::string(name));
	if (it == _textFormats.end())
		return false;

	_textFormats.erase(std::string(name));
	return true;
}

TextFormat* TextSystem::GetTextFormat(std::string_view name)
{
	TextFormatConstIterator it = _textFormats.find(std::string(name));
	if (it == _textFormats.end())
		return nullptr;
	return it->second.get();
}

WriteFactory* TextSystem::GetWriteFactory() const
{
	return _writeFactory.get();
}
