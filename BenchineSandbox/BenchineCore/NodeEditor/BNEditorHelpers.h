#pragma once
#include <imgui_node_editor.h>
#include <vector>
// Cleaning up the namespace name
namespace NodeEd = ax::NodeEditor;

// Enums
enum class NodeType
{
	Script,
	Comment,
	Flow
};

enum class PinSide
{
	Input,
	Output
};

static uint32_t nextId = 1U;
static uint32_t GetNextId()
{
	return nextId++;
}
// Graph Structs
struct Pin; // forward declare
struct Node
{
	explicit Node(const std::string& name, NodeType type, const ImColor& color = ImColor(255, 255, 255))
		: nodeId(GetNextId())
		, nodeName(name)
		, nodeType(type)
		, nodeColor(color)
		, inputPins()
		, outputPins()
	{}

	NodeEd::NodeId nodeId;
	std::string nodeName;
	NodeType nodeType;
	ImColor nodeColor;
	std::vector<Pin> inputPins;
	std::vector<Pin> outputPins;
};

struct Pin
{
	explicit Pin(const std::string& name, const std::string& type, NodeEd::PinKind side)
		: pinId(GetNextId())
		, pinName(name)
		, pinType(type)
		, pinSide(side)
	{}

	NodeEd::PinId pinId;
	std::string pinName;
	std::string pinType;
	NodeEd::PinKind pinSide;
};

struct Link
{
	explicit Link(uint32_t inId, uint32_t outId, const ImColor& color = ImColor(255, 255, 255))
		: linkId(GetNextId())
		, inputId(inId)
		, outputId(outId)
		, linkColor(color)
	{}

	explicit Link(NodeEd::PinId inId, NodeEd::PinId outId, const ImColor& color = ImColor(255, 255, 255))
		: linkId(GetNextId())
		, inputId(inId)
		, outputId(outId)
		, linkColor(color)
	{}

	NodeEd::LinkId linkId;
	NodeEd::PinId inputId;
	NodeEd::PinId outputId;
	ImColor linkColor;
};

namespace BNEHelpers
{
#pragma region Structuring
	inline void BeginColumn()
	{
		ImGui::BeginGroup();
	}

	inline void NextColumn()
	{
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
	}

	inline void EndColumn()
	{
		ImGui::EndGroup();
	}
#pragma endregion Structuring


#pragma region Builders
	void BuildNode(const Node& node) noexcept;

#pragma endregion Builders
}