#include "BenchinePCH.h"
#include "NodeEditor/BNEditorHelpers.h"

#pragma region Builders
void BNEHelpers::BuildNode(const Node& node) noexcept
{
	// Start the node
	NodeEd::BeginNode(node.nodeId);
	// Set node name
	ImGui::Text(node.nodeName.c_str());
	// Set input pins
	BeginColumn();
	for (auto& pin : node.inputPins)
	{
		NodeEd::BeginPin(pin.pinId, pin.pinSide);
		// Set pin name
		ImGui::Text(pin.pinName.c_str());
		NodeEd::EndPin();
	}
	// Set output pins
	NextColumn();
	for (auto& pin : node.outputPins)
	{
		NodeEd::BeginPin(pin.pinId, pin.pinSide);
		// Set pin name
		ImGui::Text(pin.pinName.c_str());
		NodeEd::EndPin();
	}
	EndColumn();
	NodeEd::EndNode();
}
#pragma endregion Builders