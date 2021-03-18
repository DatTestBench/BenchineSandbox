#include "BenchinePCH.h"
#include "Debugging/Logger.hpp"

#include <regex>
#include "Core/BenchineCore.hpp"
#include <magic_enum/magic_enum.hpp>

void Logger::OutputLog() noexcept
{
	m_LogList.remove_if([] (const LogEntry& entry) { return entry.markedForClear; });

	if (ImGui::Begin("Log"))
	{
		if (ImGui::BeginCombo("LevelSelection", ENUM_TO_C_STR(m_CurrentLevel)))
		{
			for (auto [level, name] : magic_enum::enum_entries<LogLevel>())
			{
				if (ImGui::Selectable(C_STR_FROM_VIEW(name)))
				{
					m_CurrentLevel = level;
				}
			}
			ImGui::EndCombo();
		}

		ImGui::SameLine();

		if (ImGui::BeginCombo("Verbosity", ENUM_TO_C_STR(m_VerbosityLevel)))
		{
			for (auto [verbosity, name] : magic_enum::enum_entries<Verbosity>())
			{
				if (ImGui::Selectable(C_STR_FROM_VIEW(name)))
				{
					m_VerbosityLevel = verbosity;
				}
			}
			ImGui::EndCombo();
		}

		u32 logLine = 1;

		const std::regex pattern(".*\\\\([a-zA-Z]*\\.(?:cpp|h(?:pp)?))");
		for (auto& log : m_LogList)
		{
			if (log.level == m_CurrentLevel || m_CurrentLevel == LogLevel::Full)
			{
				if (ImGui::SmallButton((std::to_string(logLine++) + "::").c_str()))
					log.markedForClear = true;

				ImGui::SameLine();
				
				std::string textOutput;

				switch (m_VerbosityLevel)
				{
				case Verbosity::MessageOnly:
					textOutput = fmt::format("{0}\n", log.message);
					break;
				case Verbosity::HeaderOnly:
					textOutput = fmt::format("[{0}] {1}\n", magic_enum::enum_name(log.level), log.message);
					break;
				case Verbosity::HeaderAndLocationCompact:
				{
					const std::string fileName = log.file.substr(log.file.find_last_of('/') + 1);
					textOutput = fmt::format("[{0}] {1} {2}:({3}) > {4}\n", magic_enum::enum_name(log.level), fileName, log.function, log.line, log.message);
					break;
				}
				case Verbosity::Full:
					textOutput = fmt::format("[{0}] {1} {2}:({3}) > {4}\n", magic_enum::enum_name(log.level), log.file, log.function, log.line, log.message);
					break;
				default:
					break;
				}

				if (!log.consoleLogged)
				{
					print(fg(COLOR_LUT.at(EnumIndex(log.level)).FmtColor), textOutput);
					log.consoleLogged = true;
				}

				ImGui::TextColored(COLOR_LUT.at(EnumIndex(log.level)).ImGuiColor, textOutput.c_str());
			}
		}
	}
	ImGui::End();
}
