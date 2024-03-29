#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Core/CoreBasicTypes.hpp"
#include "Helpers/Concepts.hpp"
class Pin;
struct Link;
class Node;
class BNEditor final
{
public:
	explicit BNEditor(const std::string& editorName);

	void Initialize();
	void Update(f32 dT) const;

	template <IsNode NodeType>
	NodeType* AddNode(NodeType* pNode)
	{
		m_pNodes.emplace_back(pNode);
		RebuildGraph();
		return pNode;
	}

	[[nodiscard]] constexpr auto IsInitialized() const noexcept -> bool { return m_IsInitialized; }

private:
	std::string m_EditorName;
	bool m_FirstFrame; // Flag set for first frame only, some actions need to be executed only once

	std::vector<std::unique_ptr<Node>> m_pNodes;
	std::vector<std::unique_ptr<Link>> m_pLinks;

	const Pin* FindPin(u32 pin) const;

	bool m_IsInitialized = false;

	void RebuildGraph() const;
};
