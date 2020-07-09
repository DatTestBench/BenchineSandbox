#pragma once
#include <imgui_node_editor.h>
#include <string>
#include "NodeEditor/BNEditorHelpers.h"



class BNEditor final
{
public:
	BNEditor(const std::string& editorName);
	~BNEditor();
	DEL_ROF(BNEditor)

		void Initialize();
	void Update(float dT);
	const Node* AddNode(const Node& node) noexcept;

private:
	std::string m_EditorName;
	NodeEd::EditorContext* m_pContext;
	bool m_FirstFrame; // Flag set for first frame only, some actions need to be executed only once
	uint32_t m_NextLinkId;

	std::vector<Node> m_Nodes;
	std::vector<Link> m_Links;

#pragma region InternalHelpers
	Node* FindNode(NodeEd::NodeId id) noexcept
	{
		for (auto& node : m_Nodes)
		{
			if (node.nodeId == id)
			{
				return &node;
			}
		}
		return nullptr;
	}

	Link* FindLink(NodeEd::LinkId id) noexcept
	{
		for (auto& link : m_Links)
		{
			if (link.linkId == id)
			{
				return &link;
			}
		}
		return nullptr;
	}

	Pin* FindPin(NodeEd::PinId id) noexcept
	{
		for (auto& node : m_Nodes)
		{
			for (auto& pin : node.inputPins)
			{
				if (pin.pinId == id)
				{
					return &pin;
				}
			}
			for (auto& pin : node.outputPins)
			{
				if (pin.pinId == id)
				{
					return &pin;
				}
			}
		}
		return nullptr;
	}

	bool IsPinLinked(NodeEd::PinId id) noexcept
	{
		for (auto& link : m_Links)
		{
			if (link.inputId == id || link.outputId == id)
			{
				return true;
			}
		}
		return false;
	}

	bool CanConnect(Pin* pStart, Pin* pEnd) noexcept
	{
		if (
			pStart->pinType == pEnd->pinType && // Check types
			pStart != pEnd && // prevent self linking
			pStart->pinSide != pEnd->pinSide // prevent linking inputs to inputs and outputs to outputs
			)
		{
			return true;
		}
		return false;
	}

	void SetPinSides(Node* pNode)
	{
		for (auto& input : pNode->inputPins)
		{
			input.pinSide = NodeEd::PinKind::Input;
		}
		for (auto& output : pNode->outputPins)
		{
			output.pinSide = NodeEd::PinKind::Output;
		}
	}
#pragma endregion InternalHelpers

	

};