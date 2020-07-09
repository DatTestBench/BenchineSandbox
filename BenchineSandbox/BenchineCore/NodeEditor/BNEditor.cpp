#include "BenchinePCH.h"
#include "NodeEditor/BNEditor.h"


BNEditor::BNEditor(const std::string& editorName)
	: m_EditorName(editorName)
	, m_pContext(nullptr)
	, m_FirstFrame(true)
	, m_NextLinkId(1U)
{

}

BNEditor::~BNEditor()
{
	NodeEd::DestroyEditor(m_pContext);
}

void BNEditor::Initialize()
{
	NodeEd::Config config;
	static std::string editorFile = m_EditorName + ".json";
	config.SettingsFile = editorFile.c_str();
	m_pContext = NodeEd::CreateEditor(&config);
	NodeEd::SetCurrentEditor(m_pContext);

}

void BNEditor::Update([[maybe_unused]] float dT)
{
	auto& io = ImGui::GetIO();
	ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.f / io.Framerate : 0.f);

	ImGui::Separator();

	NodeEd::SetCurrentEditor(m_pContext);

	// Start Interaction with editor
	NodeEd::Begin(m_EditorName.c_str());

	auto cursorPos = ImGui::GetCursorScreenPos();



	// Nodes
	for (auto& node : m_Nodes)
	{
		BNEHelpers::BuildNode(node);
	}

	// Links
	for (auto& link : m_Links)
	{
		NodeEd::Link(link.linkId, link.inputId, link.outputId);
	}

	// Interaction
	if (NodeEd::BeginCreate())
	{
		NodeEd::PinId startPinId, endPinId;
		if (NodeEd::QueryNewLink(&startPinId, &endPinId))
		{
			auto startPin = FindPin(startPinId);
			auto endPin = FindPin(endPinId);
			if (CanConnect(startPin, endPin))
			{
				// In case the user is connecting an input to an ouput
				if (startPin->pinSide == NodeEd::PinKind::Input)
				{
					std::swap(startPin, endPin);
					std::swap(startPinId, endPinId);
				}

				if (NodeEd::AcceptNewItem(ImColor(128, 255, 128), 4.0f))
				{
					m_Links.emplace_back(Link(startPinId, endPinId));
				}
			}
		}
	}
	NodeEd::EndCreate();

	if (NodeEd::BeginDelete())
	{
		NodeEd::LinkId deletedLinkId;
		while (NodeEd::QueryDeletedLink(&deletedLinkId))
		{
			if (NodeEd::AcceptDeletedItem())
			{
				for (auto& link : m_Links)
				{
					if (link.linkId == deletedLinkId)
					{
						m_Links.erase(std::remove_if(m_Links.begin(), m_Links.end(), [link](const Link& l) { return l.linkId == link.linkId; }), m_Links.begin());
						break;
					}
				}
			}
		}
	}
	NodeEd::EndDelete();


	NodeEd::End();
	NodeEd::SetCurrentEditor(nullptr);
}

const Node* BNEditor::AddNode(const Node& node) noexcept
{
	m_Nodes.emplace_back(node);
	return &node;
}