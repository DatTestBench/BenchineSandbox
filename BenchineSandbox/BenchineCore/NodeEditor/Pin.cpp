#include "NodeEditor/Pin.hpp"

#include "Debugging/Logger.hpp"

#include "ImGui/imgui.h"

#include "ImNodes/imnodes.h"

#include "NodeEditor/BNEditorHelpers.h"
#include "NodeEditor/Node.hpp"

Pin::Pin(const std::string& name, Node* pOwner, const PinSide side, const std::string& type)
	: m_Id(GetNextId())
	, m_Name(name)
	, m_Type(type)
	, m_Side(side)
	, m_pParentNode(pOwner)
{
}

void Pin::Construct() const
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

bool Pin::StartConnection(Pin* pOther)
{
	if (m_Type == pOther->GetType())
	{
		if (pOther->AcceptConnection(this))
		{
			m_Connections.push_back(pOther);
			return true;
		}

		LOG(Error, "{pin} on {node} attempted to engage valid connection with {otherPin} on {otherNode}. {otherPin} did not accept.",
		    fmt::arg("pin", GetFormattedString()),
		    fmt::arg("node", m_pParentNode->GetFormattedString()),
		    fmt::arg("otherPin", pOther->GetFormattedString()),
		    fmt::arg("otherNode", pOther->GetParentNode()->GetFormattedString())
		);

		return false;
	}

	return false;
}
bool Pin::AcceptConnection(Pin* pOther)
{
	if (m_Type == pOther->GetType())
	{
		m_Connections.push_back(pOther);
		return true;
	}
	return false;
}

std::string Pin::GetFormattedString() const noexcept
{
	return fmt::format(
		"\nPin {name}, {id}"
		"Type {type}"
		"Owner {ownerName}"
		"Connections {connectionCount}",
		fmt::arg("name", m_Name),
		fmt::arg("id", m_Id),
		fmt::arg("type", m_Type),
		fmt::arg("ownerName", m_pParentNode->GetName()),
		fmt::arg("connectionCount", m_Connections.size())
	);
}
