#ifndef GRAPHLYUI_TEXTSYSTEM_HEADER
#define GRAPHLYUI_TEXTSYSTEM_HEADER

#include "TextFormat.h"
#include "WriteFactory.h"

#include <unordered_map>

namespace GraphlyUI
{
	class TextSystem final
	{
		using TextFormatIterator = std::unordered_map<std::string, TextFormatPtr>::iterator;
		using TextFormatConstIterator = std::unordered_map<std::string, TextFormatPtr>::const_iterator;

	public:
		TextSystem();
		TextSystem(const TextSystem& other) = delete;
		TextSystem(TextSystem&& other) = delete;
		~TextSystem() = default;

		TextFormat* CreateTextFormat(std::string_view name, const TextFormatSettings& settings);
		TextFormat* CreateTextFormat(std::string_view name, TextFormatSettings&& settings);
		bool DestroyTextFormat(std::string_view name);
		[[nodiscard]] TextFormat* GetTextFormat(std::string_view name);
		[[nodiscard]] WriteFactory* GetWriteFactory() const;

		TextSystem& operator = (const TextSystem& other) = delete;
		TextSystem& operator = (TextSystem&& other) = delete;

	private:
		[[nodiscard]] bool Initialize();

	private:
		std::unordered_map<std::string, TextFormatPtr> _textFormats{}; 

		WriteFactoryPtr _writeFactory{};
	};

	using TextSystemPtr = std::unique_ptr<TextSystem>;
	using TextSystemSharedPtr = std::shared_ptr<TextSystem>;
}

#endif // GRAPHLYUI_TEXTSYSTEM_HEADER
