#ifndef LOGGER_HPP
#define LOGGER_HPP

// General Includes
#include <list>
#include <array>

// Project Includes
#include "fmt/color.h"
#include "Helpers/Singleton.hpp"
#include "magic_enum/magic_enum.hpp"
#include "fmt/format.h" // shows up as unused, used in macro

enum class LogLevel : int16_t
{
	Success = 0,
    LEVEL_SUCCESS = Success,
    Debug = 1,
    LEVEL_DEBUG = Debug,
    Info = 2,
    LEVEL_INFO = Info,
    Warning = 3,
    LEVEL_WARNING = Warning,
    Error = 4,
    LEVEL_ERROR = Error,
    Full = 5, // Only used to for displaying in the log window, should not be passed to logentries
    LEVEL_FULL = Full // Only used to for displaying in the log window, should not be passed to logentries
};

enum class Verbosity : uint16_t
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
	#define LOG_CONSOLE(level, ...) fmt::print("[{0}] {1} {2}({3}): {4}\n", magic_enum::enum_name(LogLevel::level), __FILE__, __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__))
	#define LOG_IMGUI(level, ...) Logger::GetInstance()->Log<LogLevel::level>(__FILE__, __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__))

#	if LOG_OUTPUT == LOG_CONSOLE_ONLY
	#define LOG(level, ...) LOG_CONSOLE(level, __VA_ARGS__)
#	elif LOG_OUTPUT == LOG_LOGGER_ONLY
	#define LOG(level, ...) LOG_IMGUI(level, __VA_ARGS__)
#	elif LOG_OUTPUT == LOG_BOTH
	#define LOG(level, ...) LOG_CONSOLE(level, __VA_ARGS__); LOG_IMGUI(level, __VA_ARGS__)
#	endif

#else
	#define LOG_CONSOLE(level, ...)UNUSED(level); UNUSED(__VA_ARGS__)
	#define LOG_IMGUI(level, ...) UNUSED(level); UNUSED(__VA_ARGS__)
    #define	LOG(level, ...) UNUSED(level); UNUSED(__VA_ARGS__)
#endif

struct LogEntry
{
	LogLevel level;
	std::string file;
	std::string function;
	uint32_t line;
	std::string message;
	bool markedForClear;
	LogEntry(const LogLevel lvl, const std::string& fl, const std::string& func, uint32_t ln, const std::string& msg = "")
		: level(lvl)
		, file(fl)
		, function(func)
		, line(ln)
		, message(msg)	
		, markedForClear(false)
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
	* @param header Name of the scope this log was called in
	* @param message Log message
	* */
	template <LogLevel Level>
	static void Log(const std::string& file, const std::string& function, uint32_t line, const std::string& message)
	{
		static_assert(Level != LogLevel::LEVEL_FULL, "LEVEL_FULL is not a valid LogLevel");
		GetInstance()->m_LogList.emplace_back(Level, file, function, line, message);
	}
	
	/**
	 * Returns string with loglevel + header structure
	 * @returns string with loglevel + header
	 * */
	std::string RawOutput(const LogLevel level, const std::string& header) const
	{
		return std::string("[" + std::string(magic_enum::enum_name(level)) + "] " + header + " > ");
	}

	/**
	 * ImGui code to output the logger window
	 * */
	void OutputLog() noexcept;


	struct ColorWrapper
	{
		ColorWrapper(const ImVec4& imCol, const fmt::color& fmtCol)
            : ImGuiColor(imCol)
            , FmtColor(fmtCol)
		{}
		
		ImVec4 ImGuiColor;
		fmt::color FmtColor;
	};
	inline static const std::array<ColorWrapper, 6> COLOR_LUT
	{
		ColorWrapper{ ImVec4{ 0.f, 1.f, 0.f, 1.f }, fmt::color::green },  // SUCCESS	
		ColorWrapper{ ImVec4{ 1.f, 0.f, 1.f, 1.f }, fmt::color::purple }, // DEBUG
		ColorWrapper{ ImVec4{ 1.f, 1.f, 1.f, 1.f }, fmt::color::white },  // INFO	
		ColorWrapper{ ImVec4{ 1.f, 1.f, 0.f, 1.f }, fmt::color::yellow }, // WARNING	
		ColorWrapper{ ImVec4{ 1.f, 0.f, 0.f, 1.f }, fmt::color::red },	  // ERROR	
		ColorWrapper{ ImVec4{ 1.f, 1.f, 1.f, 1.f }, fmt::color::white }   // DEFAULT
	};
	

private:


	std::list<LogEntry> m_LogList;
	bool m_ShowHeaders = true;
	LogLevel m_CurrentLevel = LogLevel::LEVEL_FULL;
	Verbosity m_VerbosityLevel = Verbosity::Full;


	const std::array<ImVec4, 6> m_ImGuiColors
	{
		ImVec4{ 0.f, 1.f, 0.f, 1.f }, // SUCCESS
		ImVec4{ 1.f, 0.f, 1.f, 1.f }, // DEBUG
		ImVec4{ 1.f, 1.f, 1.f, 1.f }, // INFO
		ImVec4{ 1.f, 1.f, 0.f, 1.f }, // WARNING
		ImVec4{ 1.f, 0.f, 0.f, 1.f },	// ERROR
		ImVec4{ 1.f, 1.f, 1.f, 1.f }	// DEFAULT
	};
};

#endif // !LOGGER_HPP
