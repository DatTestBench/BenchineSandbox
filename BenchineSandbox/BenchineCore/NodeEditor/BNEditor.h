#pragma once
#include <imgui_node_editor.h>

namespace NodeEd = ax::NodeEditor;

struct LinkInfo
{
	NodeEd::LinkId id;
	NodeEd::PinId inputId;
	NodeEd::PinId outputId;
};


namespace BNEHelpers
{
	void BeginColumn()
	{
		ImGui::BeginGroup();
	}

	void NextColumn()
	{
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
	}

	void EndColumn()
	{
		ImGui::EndGroup();
	}
}



class BNEditor final
{
public:
	BNEditor();
	~BNEditor();
	DEL_ROF(BNEditor);

	Update(float dT);

private: 
	NodeEd::EditorContext* m_pContext;
	bool m_FirstFrame; // Flag set for first frame only, some actions need to be executed only once
	std::vector<LinkInfo> m_Links; // List of live links
	uint32_t m_NextLinkId;
}