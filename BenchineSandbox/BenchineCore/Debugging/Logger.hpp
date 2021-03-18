#ifndef LOGGER_HPP
#define LOGGER_HPP

// General Includes
#include <list>
#include <array>

// Project Includes
#include "fmt/color.h"
#include "Helpers/Singleton.hpp"
#include "Core/BenchineCore.hpp"
//#include "fmt/format.h"

enum class LogLevel : u16
{
	Success = 0,
	Debug = 1,
	Info = 2,
	Warning = 3,
	Error = 4,
	Full = 5, // Only used to for displaying in the log window, should not be passed to logentries
};

enum class Verbosity : u16
{
	MessageOnly = 0,
	HeaderOnly = 1,
	HeaderAndLocationCompact = 2,
	Full = 3
};

#define DEBUG_OVERRIDE 1

#define LOG_CONSOLE_ONLY 1
#define LOG_LOGGER_ONLY 2
#define LOG_BOTH 3

#define LOG_OUTPUT LOG_LOGGER_ONLY

#if !NDEBUG || DEBUG_OVERRIDE
	#define LOG_CONDITIONAL(condition, level, ...) if (condition) LOG(level, __VA_ARGS__)
	#define LOG(level, ...) Logger::GetInstance()->Log<LogLevel::level>(__FILE__, __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__))
#else
	#define LOG_CONDITIONAL(condition, level, ...) UNUSED(condition); UNUSED(level); UNUSED(__VA_ARGS__)
    #define	LOG(level, ...) UNUSED(level); UNUSED(__VA_ARGS__)
#endif

struct LogEntry
{
	LogLevel level;
	std::string file;
	std::string function;
	u32 line;
	std::string message;
	bool markedForClear;
	bool consoleLogged;
	LogEntry(const LogLevel lvl, const std::string& fl, const std::string& func, const u32 ln, const std::string& msg = "")
		: level(lvl)
		, file(fl)
		, function(func)
		, line(ln)
		, message(msg)
		, markedForClear(false)
		, consoleLogged(false)
	{
	}
};

class Logger final : public Singleton<Logger>
{
public:
	explicit Logger(Token)
	{
	}

	/**
	* Log Function 
	* @template Level LogLevel
	* @param file
	* @param function
	* @param line
	* @param message Log message
	* */
	template <LogLevel Level>
	static void Log(const std::string& file, const std::string& function, uint32_t line, const std::string& message)
	{
		static_assert(Level != LogLevel::Full, "LEVEL_FULL is not a valid LogLevel");
		GetInstance()->m_LogList.emplace_back(Level, file, function, line, message);
	}

	/**
	 * ImGui code to output the logger window
	 * */
	void OutputLog() noexcept;

	struct OutputWrapper
	{
		OutputWrapper(const ImVec4& imCol, const fmt::color& fmtCol)
			: ImGuiColor(imCol)
			, FmtColor(fmtCol)
		{
		}

		ImVec4 ImGuiColor;
		fmt::color FmtColor;
	};

private:
	std::list<LogEntry> m_LogList;
	bool m_ShowHeaders = true;
	LogLevel m_CurrentLevel = LogLevel::Full;
	Verbosity m_VerbosityLevel = Verbosity::Full;

	inline static const std::array<OutputWrapper, 6> COLOR_LUT
	{
		OutputWrapper{ ImVec4{ 0.f, 1.f, 0.f, 1.f }, fmt::color::green },  // SUCCESS	
		OutputWrapper{ ImVec4{ 1.f, 0.f, 1.f, 1.f }, fmt::color::purple }, // DEBUG
		OutputWrapper{ ImVec4{ 1.f, 1.f, 1.f, 1.f }, fmt::color::white },  // INFO	
		OutputWrapper{ ImVec4{ 1.f, 1.f, 0.f, 1.f }, fmt::color::yellow }, // WARNING	
		OutputWrapper{ ImVec4{ 1.f, 0.f, 0.f, 1.f }, fmt::color::red },	  // ERROR	
		OutputWrapper{ ImVec4{ 1.f, 1.f, 1.f, 1.f }, fmt::color::white }   // DEFAULT
	};
};

#endif // !LOGGER_HPP
