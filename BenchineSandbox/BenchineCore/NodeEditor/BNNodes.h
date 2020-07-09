#pragma once
#include "NodeEditor/BNEditor.h"
#include <vector>

namespace Nodes
{
	static Node SpawnPrintNode()
	{
		Node node{ "Print", NodeType::Script, ImColor(255, 255, 255) };
		node.inputPins.emplace_back(Pin("O", "Flow", NodeEd::PinKind::Input));
		node.inputPins.emplace_back(Pin("Text", "String", NodeEd::PinKind::Input));

		node.outputPins.emplace_back(Pin("O", "Flow", NodeEd::PinKind::Output));

		return node;
	}

	static Node SpawnAddition()
	{
		Node node{ "+", NodeType::Script };

		node.inputPins.emplace_back(Pin("o a", "Int", NodeEd::PinKind::Input));
		node.inputPins.emplace_back(Pin("o b", "Int", NodeEd::PinKind::Input));

		node.outputPins.emplace_back(Pin("o", "Int", NodeEd::PinKind::Output));

		return node;
	}

	static Node SpawnInt()
	{
		Node node{ "INT", NodeType::Script };
		node.outputPins.emplace_back(Pin("o", "Int", NodeEd::PinKind::Output));

		return node;
	}

	static Node SpawnIntToString()
	{
		Node node{ "IntToString", NodeType::Script };
		node.inputPins.emplace_back(Pin("o", "Int", NodeEd::PinKind::Input));

		node.outputPins.emplace_back(Pin("o", "String", NodeEd::PinKind::Output));

		return node;
	}
}