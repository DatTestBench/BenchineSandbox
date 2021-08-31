#pragma once
#include "Core/BaseGame.h"
class Sandbox final : public BaseGame
{
public:
	explicit Sandbox(const std::string_view name) : BaseGame(name) {}

protected:
	void Initialize() override;
	void Update([[maybe_unused]] f32 dT) override;
};