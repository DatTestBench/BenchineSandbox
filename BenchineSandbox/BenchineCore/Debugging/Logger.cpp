#include "BenchinePCH.h"
#include "Debugging/Logger.h"

void Logger::OutputLog()
{
	m_LogList.erase(std::remove_if(m_LogList.begin(), m_LogList.end(), [](const LogEntry& entry) { return entry.MarkedForClear; }), m_LogList.end());

	if (ImGui::Begin("Log"))
	{
		if (ImGui::BeginCombo("LevelSelection", m_LevelTags.at(m_CurrentLevel).c_str())) // Reference to implementation https://github.com/ocornut/imgui/issues/1658
		{
			for (size_t i = 0; i < m_LevelTags.size(); i++)
			{
				if (ImGui::Selectable(m_LevelTags.at(i).c_str(), m_CurrentLevel == i))
				{
					m_CurrentLevel = static_cast<LogLevel>(i);
				}
			}
			ImGui::EndCombo();
		}

		ImGui::SameLine();

		ImGui::Checkbox("Show Headers", &m_ShowHeaders);

		int logLine = 1;
		for (auto& log : m_LogList)
		{
			if (log.OutputLocation == LOG_IMGUI)
			{
				if (log.Level == m_CurrentLevel || m_CurrentLevel == LEVEL_FULL)
				{
					if (ImGui::SmallButton((std::to_string(logLine++) + "::").c_str()))
					{
						log.MarkedForClear = true;
					}

					ImGui::SameLine();

					if (m_ShowHeaders)
					{
						ImGui::TextColored(m_ImGuiColors.at(log.Level), ("[" + m_LevelTags.at(log.Level) + "] " + log.Header + " > " + log.Message.str()).c_str(), 0);
					}
					else
					{
						ImGui::LogText("");
						ImGui::TextColored(m_ImGuiColors.at(log.Level), log.Message.str().c_str(), 0);
					}
				}
			}
			if (log.OutputLocation == LOG_CONSOLE)
			{
				// TODO: fix repeat console output
				std::cout << "[" + m_LevelTags.at(log.Level) + "]" + log.Header + " > " + log.Message.str() << "\n";
			}
		}
	}
	ImGui::End();
}