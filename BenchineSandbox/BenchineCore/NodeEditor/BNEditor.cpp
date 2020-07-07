#include "BenchinePCH.h"
#include "NodeEditor/BNEditor.h"

BNEditor::BNEditor()
	: m_pContext(nullptr)
	, m_FirstFrame(true)
	, m_Links()
	, m_NextLinkId(1U)
{

}

BNEditor::~BNEditor()
{
	NodeEd::DestroyEditor(m_pContext);
}

BNEditor::Update([[maybe_unused]] float dT)
{
	auto& io = ImGui::GetIO();
	ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.f / io.Framerate : 0.f);

	ImGui::Separator();

	NodeEd::SetCurrentEditor(m_pContext);

	// Start Interaction with editor
}