#pragma once
#include "Pin.hpp"

enum class NodeType
{
	Script,
	Comment,
	Flow
};

class Node
{
public:
	explicit Node(std::string_view name);

	virtual ~Node() = default;

	void InitBase();
	void BuildBase();

	const Pin* AddPin(PinSide side, std::string_view name) noexcept;

	[[nodiscard]] constexpr auto GetName() const noexcept -> std::string_view { return m_Name; }

	[[nodiscard]] std::string GetFormattedString() const noexcept;

	[[nodiscard]] const Pin* GetPin(u32 id) const noexcept;

protected:
	u32 m_Id;
	std::string_view m_Name;
	virtual void Init() = 0;
	virtual void Build() = 0;

private:
	std::vector<Pin> m_InputPins;
	std::vector<Pin> m_OutputPins;
};
