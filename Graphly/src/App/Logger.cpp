#include "Graphly/App/Logger.h"

#include <windows.h>

using namespace Graphly;

Logger::Logger(const LoggerSettings& settings)
: _settings(settings)
{
	if (!Initialize())
		throw std::runtime_error("Logger failed to initialize.");
}

Logger::Logger(LoggerSettings&& settings)
: _settings(std::forward<LoggerSettings>(settings))
{
	if (!Initialize())
		throw std::runtime_error("Logger failed to initialize.");
}

bool Logger::Initialize()
{
	bool noValue = false;

	if (!_settings.logPath.has_value())
	{
		_settings.logPath = "GraphlyLogs.txt";
		noValue = true;
	}

	[[unlikely]] if (_settings.logPath.value().empty())
	{
		WritePopupMessage({ MessageType::Error, "Log file path was empty!\n" });
		return false;
	}

	_logFile.open(_settings.logPath.value());
	[[unlikely]] if (!_logFile.is_open())
	{
		WritePopupMessage({ MessageType::Error, "Log file with path " + _settings.logPath.value() + " cannot be opened!" });
		return false;
	}

	if (noValue)
		WriteLogMessage({ MessageType::Warning, "No log path was given! Default path for log file was set to ${workingDir}GraphlyLogs.txt\n" });

	return true;
}

Logger::~Logger()
{
	_logFile.close();
}

void Logger::WriteLogMessage(const Message& msg)
{
	WriteLogMessageImpl(Message(msg));
}

void Logger::WriteLogMessage(Message&& msg)
{
	WriteLogMessageImpl(std::move(msg));
}

void Logger::WritePopupMessage(const Message& msg)
{
	WritePopupMessageImpl(Message(msg));
}

void Logger::WritePopupMessage(Message&& msg)
{
	WritePopupMessageImpl(std::move(msg));
}

void Logger::WriteLogMessageImpl(Message&& msg)
{
	switch (msg.type)
	{
	case MessageType::Information:
		_logFile << "[Information]: ";
		break;
	case MessageType::Warning:
		_logFile << "[Warning]: ";
		break;
	case MessageType::Error:
		_logFile << "[Error]: ";
		break;
	default:
		throw std::runtime_error("Undefined message type.");
	}

	_logFile << msg.str;
}

void Logger::WritePopupMessageImpl(Message&& msg)
{
	std::string caption;
	UINT type = MB_OK;

	switch (msg.type)
	{
	case MessageType::Information:
		caption = "[Information]: ";
		type |= MB_ICONINFORMATION;
		break;
	case MessageType::Warning:
		caption = "[Warning]: ";
		type |= MB_ICONWARNING;
		break;
	case MessageType::Error:
		caption = "[Error]: ";
		type |= MB_ICONERROR;
		break;
	default:
		throw std::runtime_error("Undefined message type.");
	}

	::MessageBoxA(HWND_DESKTOP, msg.str.c_str(), caption.c_str(), type);
}

std::string& Logger::GetLogFilePath()
{
	return _settings.logPath.value();
}
