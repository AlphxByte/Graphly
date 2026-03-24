#ifndef GRAPHLY_LOGGER_HEADER
#define GRAPHLY_LOGGER_HEADER

#include <memory>
#include <fstream>
#include <optional>

namespace Graphly
{
	enum class MessageType
	{
		Information = 0,
		Warning,
		Error
	};

	struct Message final
	{
		MessageType type{};
		std::string str{};
	};

	using LogPath = std::optional<std::string>;

	struct LoggerSettings final
	{
		LogPath logPath;
	};

	class Logger final
	{
	public:
		Logger(const LoggerSettings& settings);
		Logger(LoggerSettings&& settings);
		Logger(const Logger& other) = delete;
		Logger(Logger&& other) = delete;
		~Logger();

		void WriteLogMessage(const Message& msg);
		void WriteLogMessage(Message&& msg);
		void WritePopupMessage(const Message& msg);
		void WritePopupMessage(Message&& msg);

		std::string& GetLogFilePath();

		Logger& operator = (const Logger& other) = delete;
		Logger& operator = (Logger&& other) = delete;

	private:
		bool Initialize();

		void WriteLogMessageImpl(Message&& msg);
		void WritePopupMessageImpl(Message&& msg);

	private:
		LoggerSettings _settings{};
		std::ofstream _logFile{};
	};

	using LoggerPtr		  = std::unique_ptr<Logger>;
	using LoggerSharedPtr = std::shared_ptr<Logger>;
}

#endif // GRAPHLY_LOGGER_HEADER
