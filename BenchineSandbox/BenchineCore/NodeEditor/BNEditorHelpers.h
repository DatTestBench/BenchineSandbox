#pragma once
#include <vector>

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

#if 0
static u32 nextId = 1U;
static u32 GetNextId()
{
	return nextId++;
}
#endif

// Graph Structs
struct Pin; // forward declare
struct Node
{
	
};

struct Pin
{
	
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


#pragma region Builders
	void BuildNode(const Node& node) noexcept;

#pragma endregion Builders
}