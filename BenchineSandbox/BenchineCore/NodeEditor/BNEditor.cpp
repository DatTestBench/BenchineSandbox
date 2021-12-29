#include "NodeEditor/BNEditor.h"

#include "ImGui/imgui.h"

#include "ImNodes/imnodes.h"

#include "NodeEditor/BNEditorHelpers.h"
#include "NodeEditor/Node.hpp"

BNEditor::BNEditor(const std::string& editorName)
	: m_EditorName(editorName)
	, m_FirstFrame(true)
{
}

void BNEditor::Initialize()
{
	// TODO: this will eventually have to be called after all the nodes are initialized, so we can just do RebuildGraph once at startup
	// Currently it will just RebuildGraph every time a node is added
	m_IsInitialized = true;
}

void BNEditor::Update(f32) const
{
	if (ImGui::Begin(m_EditorName.c_str()))
	{
		ImNodes::BeginNodeEditor();
		for (auto&& pNode : m_pNodes)
		{
			pNode->BuildBase();
		}

		ImNodes::EndNodeEditor();


		// TODO: If there's a newly created link, retrieve it from the editor
		// u32 start, end;
	}
	ImGui::End();
}


const Pin* BNEditor::FindPin(const u32 pin) const
{
	for (auto&& pNode : m_pNodes)
	{
		if (const auto pPin = pNode->GetPin(pin))
		{
			return pPin;
		}
	}

	return nullptr;
}
void BNEditor::RebuildGraph() const
{
	for (auto&& pNode : m_pNodes)
	{
		pNode->InitBase();
	}
}
