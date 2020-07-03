#pragma once

#include "Helpers/Singleton.h"

#include <array>

enum LogLevel : uint16_t
{
	LEVEL_DEBUG,
	LEVEL_INFO,
	LEVEL_WARNING,
	LEVEL_ERROR,
	LEVEL_FULL // Only used to for displaying in the log window, should not be passed to logentries
};

enum LogArgument : uint16_t
{
	LOG_IMGUI,
	LOG_CONSOLE
};

struct LogEntry
{
	std::string Header;
	std::stringstream Message;
	LogLevel Level;
	LogArgument OutputLocation;
	bool MarkedForClear;
	LogEntry(const std::string& log, LogLevel level, LogArgument outputLocation)
		: Header(log)
		, Message()
		, Level(level)
		, OutputLocation(outputLocation)
		, MarkedForClear(false)

	{
	}
};

class Logger : public Singleton<Logger>
{
public:

	Logger(token) {}

	/**
	 * Log Function 
	 * @param level <T> LogLevel
	 * @param header Name of the scope this log was called in
	 * */
	template<LogLevel level, LogArgument outputLocation = LogArgument::LOG_IMGUI>
	static Logger& Log(const std::string& header = "")
	{
		static_assert(level != LEVEL_FULL, "LEVEL_FULL is not a valid LogLevel");

		GetInstance()->m_LogList.emplace_back(LogEntry(header, level, outputLocation));
		return *GetInstance();
	}

	/**
	 * Ostream for extra log messages
	 * @param log Log message
	 * */
	template<class T>
	Logger& operator<<(const T& log)
	{
		m_LogList.back().Message << log;
		return *GetInstance();
	}

	void OutputLog();

private:


	std::list<LogEntry> m_LogList;
	bool m_ShowHeaders = true;
	LogLevel m_CurrentLevel = LEVEL_FULL;

	const std::array<ImVec4, 5> m_ImGuiColors
	{
		ImVec4{ 1.f, 0.f, 1.f, 1.f }, // DEBUG
		ImVec4{ 1.f, 1.f, 1.f, 1.f }, // INFO
		ImVec4{ 1.f, 1.f, 0.f, 1.f }, // WARNING
		ImVec4{ 1.f, 0.f, 0.f, 1.f },	// ERROR
		ImVec4{ 1.f, 1.f, 1.f, 1.f }	// DEFAULT
	};

	const std::array<std::string, 5> m_LevelTags
	{
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR",
		"FULL" // Only used to for displaying in the log window, should not be passed to logentries
	};
};