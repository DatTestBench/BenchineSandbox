#pragma once
#include "Core/BaseGame.h"
class Sandbox final : public BaseGame
{
public:
	Sandbox() = default;

protected:
	void Initialize() override;
	void Update([[maybe_unused]] f32 dT) override;
};