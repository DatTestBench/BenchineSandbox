#pragma once
#define NODE_BASE(nodeName) explicit nodeName(const std::string_view name) : Node(name) {}
#include "BNEditorHelpers.h"

namespace Nodes
{
	class DummyNode final : public Node
	{
	public:
		NODE_BASE(DummyNode)
	
	protected:
		void Init() override
		{
			AddPin(PinSide::Input, "InputDummy");
			AddPin(PinSide::Output, "OutputDummy");
		}

		void Build() override
		{
			ImGui::Text(m_Name.data());
		}
	};
}
