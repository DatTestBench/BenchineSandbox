#pragma once
#include <string>
#include <vector>

#include "Core/CoreBasicTypes.hpp"

class Node;

enum class PinSide
{
	Input,
	Output
};

class Pin
{
public:
	explicit Pin(const std::string& name, Node* pOwner, PinSide side, const std::string& type);

	[[nodiscard]] constexpr auto GetType() const noexcept -> std::string { return m_Type; }

	void Construct() const;

	[[nodiscard]] bool StartConnection(Pin* pOther);

	bool AcceptConnection(Pin* pOther);

	[[nodiscard]] std::string GetFormattedString() const noexcept;
	[[nodiscard]] constexpr auto GetConnectionCount() const noexcept -> u32 { return static_cast<u32>(m_Connections.size()); }
	[[nodiscard]] constexpr auto GetParentNode() const noexcept -> Node* { return m_pParentNode; }
	[[nodiscard]] constexpr auto GetId() const noexcept -> u32 { return m_Id; }
private:
	u32 m_Id;
	std::string m_Name;
	std::string m_Type;
	PinSide m_Side;
	Node* m_pParentNode;
	std::vector<Pin*> m_Connections;
};
