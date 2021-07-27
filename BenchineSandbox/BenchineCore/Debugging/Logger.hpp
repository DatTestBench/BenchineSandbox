#ifndef LOGGER_HPP
#define LOGGER_HPP

// General Includes
#include <list>
#include <array>
#include <string_view>
#include <source_location>

// Project Includes
#include "fmt/color.h"
#include "Helpers/Singleton.hpp"
#include "Core/BenchineCore.hpp"

enum class LogLevel : u8
{
	Success = 0,
	Debug = 1,
	Info = 2,
	Warning = 3,
	Error = 4,
	Full = 5
};

enum class Verbosity : u8
{
	MessageOnly = 0,
	HeaderOnly = 1,
	HeaderAndLocationCompact = 2,
	Full = 3
};

#ifdef B_DEBUG
	#define LOG_CONDITIONAL(condition, level, ...) if (condition) LOG(level, __VA_ARGS__)
	//#define LOG(level, ...) Logger::GetInstance()->Log<LogLevel::level>(__FILE__, __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__))
	#define LOG(level, ...) Logger::GetInstance()->Log<LogLevel::level>(fmt::format(__VA_ARGS__))
#else
	#define LOG_CONDITIONAL(condition, level, ...) UNUSED(condition, LogLevel::level, __VA_ARGS__)
    #define	LOG(level, ...) UNUSED(LogLevel::level, __VA_ARGS__)
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
	
	/**
	 * \brief Entry of a log line. Contains all the necessary information for each log entry.
	 * \param lvl Log level
	 * \param fl File name
	 * \param func Function name
	 * \param ln Line number
	 * \param msg Log message
	 */
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
	explicit Logger(Token){}

	#ifdef _SOURCE_LOCATION_
	/**
	* \brief Log Function 
	* \template Level Log level
	* \param message Log message
	* \param location Leave default https://en.cppreference.com/w/cpp/utility/source_location
	* */
	template <LogLevel Level>
	static void Log(const std::string& message, const std::source_location& location = std::source_location::current())
	{
		// TODO figure out if I want a static_assert or a fancy concept for this
		static_assert(Level != LogLevel::Full, "Full is not a valid LogLevel");
		GetInstance()->m_LogList.emplace_back(Level, location.file_name(), location.function_name(), location.line(), message);

		// Console output log
		const std::string fileName = std::string(location.file_name()).substr(std::string(location.file_name()).find_last_of('\\') + 1);
		const std::string textOutput = fmt::format("[{0}] {1} {2}:({3}) > {4}\n", magic_enum::enum_name(Level), fileName, location.function_name(), location.line(), message);
		fmt::print(fg(COLOR_LUT.at(EnumIndex(Level)).FmtColor), textOutput);
	}
	#else
	/**
	* \brief Log Function 
	* \template Level Log level
	* \param file File name
	* \param function Function name
	* \param line Line where this log was called
	* \param message Log message
	* */
	template <LogLevel Level>
    static void Log(const std::string& file, const std::string& function, const u32 line, const std::string& message)
	{
		// TODO figure out if I want a static_assert or a fancy concept for this
		static_assert(Level != LogLevel::Full, "Full is not a valid LogLevel");
		GetInstance()->m_LogList.emplace_back(Level, file, function, line, message);

		// Console output log
		const std::string fileName = file.substr(file.find_last_of('\\') + 1);
		const std::string fileName = std::string(location.file_name()).substr(std::string(location.file_name()).find_last_of('\\') + 1);
		const std::string textOutput = fmt::format("[{0}] {1} {2}:({3}) > {4}\n", magic_enum::enum_name(Level), fileName, function, line, message);
		fmt::print(fg(COLOR_LUT.at(EnumIndex(Level)).FmtColor), textOutput);
	}
	#endif

	// ImGui code to output the logger window
	void OutputLog() noexcept;

	struct OutputWrapper
	{
		/**
		 * \brief Wrapper around ImGui and fmt/std::format logging colors.
		 * \param imCol ImGui color value
		 * \param fmtCol fmt/std::format color value
		 */
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
	LogLevel m_LogLevel = LogLevel::Full;
	Verbosity m_VerbosityLevel = Verbosity::HeaderAndLocationCompact;

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
