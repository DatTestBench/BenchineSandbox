#pragma once
#include "Core/CoreBasicTypes.hpp"

#include "ImGui/imgui.h"

class Node;

// Enums




static u32 nextId = 1U;
inline extern u32 GetNextId()
{
	return nextId++;
}

// General helpers

// Graph Structs



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
