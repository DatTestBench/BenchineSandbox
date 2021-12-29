#include "NodeEditor/Node.hpp"

#include <numeric>

#include "fmt/format.h"

#include "ImNodes/imnodes.h"

#include "NodeEditor/BNEditorHelpers.h"
#include "NodeEditor/Pin.hpp"

Node::Node(const std::string_view name)
	: m_Id(GetNextId())
	, m_Name(name)
{
}
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

	for (auto& pin : m_InputPins)
	{
		pin.Construct();
	}

	for (auto& pin : m_OutputPins)
	{
		pin.Construct();
	}

	ImNodes::EndNode();
}

const Pin* Node::AddPin(PinSide side, const std::string_view name) noexcept
{
	switch (side)
	{
	case PinSide::Input:
		m_InputPins.emplace_back(fmt::format("Input_{0}", name), this, side, "void");
		return &m_InputPins.back();
	case PinSide::Output:
		m_OutputPins.emplace_back(fmt::format("Output_{0}", name), this, side, "void");
		return &m_OutputPins.back();
	}
	return nullptr;
}
std::string Node::GetFormattedString() const noexcept
{
	auto connectionCount = [] (const u32 sum, const Pin& pin) { return sum + pin.GetConnectionCount(); };
	const u32 inputConnectionCount = std::accumulate(m_InputPins.cbegin(), m_InputPins.cend(), 0U, connectionCount);
	const u32 outputConnectionCount = std::accumulate(m_OutputPins.cbegin(), m_OutputPins.cend(), 0U, connectionCount);

	return fmt::format(
		"\nNode {name}, {id}"
		"Description {description}"
		"Connections {connectionCount} (in: {inputCount}, out: {outputCount}",
		fmt::arg("name", m_Name),
		fmt::arg("id", m_Id),
		fmt::arg("description", ""), // TODO: add node descriptions
		fmt::arg("connectionCount", inputConnectionCount + outputConnectionCount),
		fmt::arg("inputCount", inputConnectionCount),
		fmt::arg("outputCount", outputConnectionCount)
	);
}
const Pin* Node::GetPin(const u32 id) const noexcept
{
	for (const auto& pin : m_InputPins)
	{
		if (pin.GetId() == id)
		{
			return &pin;
		}
	}

	for (const auto& pin : m_OutputPins)
	{
		if (pin.GetId() == id)
		{
			return &pin;
		}
	}

	return nullptr;
}
