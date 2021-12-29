#pragma once
#include <string_view>

#include "Core/CoreBasicTypes.hpp"
class BaseGame
{
public:
	explicit BaseGame(const std::string_view name)
		: m_Name(name)
	{
	}
	virtual ~BaseGame() = default;

	void BaseInitialize();
	void BaseUpdate(f32 dT);

	[[nodiscard]] constexpr auto GetGameName() const noexcept -> std::string_view { return m_Name; }

protected:
	virtual void Initialize() = 0;
	virtual void Update([[maybe_unused]] f32 dT) = 0;

private:
	std::string_view m_Name;
};
