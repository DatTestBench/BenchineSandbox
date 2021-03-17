#include "BenchinePCH.h"
#include "NodeEditor/BNEditor.h"


BNEditor::BNEditor(const std::string& editorName)
	: m_EditorName(editorName)
	, m_FirstFrame(true)
	, m_NextLinkId(1U)
{
}

BNEditor::~BNEditor()
{
}

void BNEditor::Initialize()
{
}

void BNEditor::Update([[maybe_unused]] f32 dT)
{
	auto& io = ImGui::GetIO();
	ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.f / io.Framerate : 0.f);
}

const Node* BNEditor::AddNode(const Node& node) noexcept
{
	m_Nodes.emplace_back(node);
	return &node;
}
