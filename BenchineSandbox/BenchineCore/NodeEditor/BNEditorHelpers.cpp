#include "BenchinePCH.h"
#include "NodeEditor/BNEditorHelpers.h"

void Node::InitBase()
{
	// NOTE: this is not ideal but it'll do for now
	if (!m_InputPins.empty())
		m_InputPins.clear();
	if (!m_OutputPins.empty())
		m_OutputPins.clear();
	
	Init();
}
void Node::BuildBase()
{
	ImNodes::BeginNode(m_Id);
	Build();

	for(auto& pin : m_InputPins)
	{
		pin.Construct();
	}

	for(auto& pin : m_OutputPins)
	{
		pin.Construct();
	}
	
	ImNodes::EndNode();
}
