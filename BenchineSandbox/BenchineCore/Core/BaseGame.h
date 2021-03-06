#pragma once
#include "Core/BenchineCore.hpp"
// Using a basegame so the engine can be reused for games other than BubbleBobble without having to rewrite the Runner
class BaseGame
{
public:
	BaseGame() = default;
	virtual ~BaseGame() = default;
	DEL_ROF(BaseGame)

	void BaseInitialize();
	void BaseUpdate(f32 dT);

	[[nodiscard]] constexpr auto GetGameName() const noexcept-> std::string_view { return m_Name; }

protected:
	virtual void Initialize() = 0;
	virtual void Update([[maybe_unused]] f32 dT) = 0;

private:
	std::string_view m_Name;
};