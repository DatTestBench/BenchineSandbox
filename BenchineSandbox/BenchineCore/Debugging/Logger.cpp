#include "BenchinePCH.h"
#include "Debugging/Logger.hpp"

#include <regex>

#include "Helpers/GeneralHelpers.hpp"

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

		uint32_t logLine = 1;

		const std::regex pattern(".*\\\\([a-zA-Z]*\\.(?:cpp|h(?:pp)?))");
		for (auto& log : m_LogList)
		{
			if (log.level == m_CurrentLevel || m_CurrentLevel == LogLevel::LEVEL_FULL)
			{
				if (ImGui::SmallButton((std::to_string(logLine++) + "::").c_str()))
					log.markedForClear = true;

				ImGui::SameLine();

				const auto logColor = COLOR_LUT.at(magic_enum::enum_integer(log.level)).ImGuiColor;
				
				switch (m_VerbosityLevel)
				{
				case Verbosity::MessageOnly:
					ImGui::TextColored(logColor, log.message.c_str());
					break;
				case Verbosity::HeaderOnly:
					ImGui::TextColored(logColor, fmt::format("[{0}] {1}", magic_enum::enum_name(log.level), log.message).c_str());
					break;
				case Verbosity::HeaderAndLocationCompact:
				{
					const std::string fileName = log.file.substr(log.file.find_last_of('/') + 1);
					ImGui::TextColored(logColor, fmt::format("[{0}] {1} {2}:({3}) > {4}", magic_enum::enum_name(log.level), fileName, log.function, log.line, log.message).c_str(), 0);
					break;
				}
				case Verbosity::Full:
					ImGui::TextColored(logColor, fmt::format("[{0}] {1} {2}:({3}) > {4}", magic_enum::enum_name(log.level), log.file, log.function, log.line, log.message).c_str(), 0);
					break;
				default: ;
				}
			}
		}
	}
	ImGui::End();
}
