#include "BenchinePCH.h"
#include "NodeEditor/BNEditor.h"


BNEditor::BNEditor(const std::string& editorName)
	: m_EditorName(editorName)
	, m_FirstFrame(true)
{
}

void BNEditor::Initialize()
{
	// TODO this will eventually have to be called after all the nodes are initialized, so we can just do RebuildGraph once at startup
	// Currently it will just RebuildGraph every time a node is added
	m_IsInitialized = true;
}

void BNEditor::Update(f32)
{
	if (ImGui::Begin(m_EditorName.c_str()))
	{
		ImNodes::BeginNodeEditor();
		for (auto&& pNode : m_pNodes)
		{
			pNode->BuildBase();
		}

		ImNodes::EndNodeEditor();
	}
	ImGui::End();
}


void BNEditor::RebuildGraph()
{
	for (auto&& pNode : m_pNodes)
	{
		pNode->InitBase();
	}
}