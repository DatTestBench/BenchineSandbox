#pragma once
#include <string>

#include "Core/CoreBasicTypes.hpp"
#include "ImGui/imgui.h"
#include "ImNodes/imnodes.h"
#include "fmt/format.h"
class Node;
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

static u32 nextId = 1U;
static u32 GetNextId()
{
	return nextId++;
}

// Graph Structs
class Pin
{
public:
	explicit Pin(const std::string& name, Node* pOwner, const PinSide side)
		: m_Id(GetNextId())
		, m_Name(name)
		, m_Side(side)
		, m_pOwnerNode(pOwner)
	{
	}

	void Construct() const
	{
		switch (m_Side)
		{
		case PinSide::Input:
		{
			ImNodes::BeginInputAttribute(m_Id);
			ImGui::Text(m_Name.c_str());
			ImNodes::EndInputAttribute();
		}
		break;
		case PinSide::Output:
		{
			ImNodes::BeginOutputAttribute(m_Id);
			ImGui::Text(m_Name.c_str());
			ImNodes::EndOutputAttribute();
		}
		break;
		default:
			break;
		}
	}

private:
	u32 m_Id;
	std::string m_Name;
	PinSide m_Side;
	Node* m_pOwnerNode;
};

class Node
{
public:
	explicit Node(const std::string_view name)
		: m_Id(GetNextId())
		, m_Name(name)
	{
	}
	void InitBase();
	void BuildBase();

	const Pin* AddPin(PinSide side, const std::string_view name) noexcept
	{
		switch (side)
		{
		case PinSide::Input:
			m_InputPins.emplace_back(fmt::format("Input_{0}", name), this, side);
			return &m_InputPins.back();
			
		case PinSide::Output:
			m_OutputPins.emplace_back(fmt::format("Output_{0}", name), this, side);
			return &m_OutputPins.back();
		}
		return nullptr;
	}

	virtual ~Node() = default;
protected:
	u32 m_Id;
	std::string_view m_Name;
	virtual void Init() = 0;
	virtual void Build() = 0;

private:
	
	std::vector<Pin> m_InputPins;
	std::vector<Pin> m_OutputPins;
};

struct Link
{
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
}
