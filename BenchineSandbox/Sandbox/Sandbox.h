#pragma once
#include "Core/BaseGame.h"
class Sandbox final : public BaseGame
{
public:
	Sandbox() = default;
	virtual ~Sandbox() override = default;
	DEL_ROF(Sandbox)

protected:
	void Initialize() override;
	void Update([[maybe_unused]] float dT) override;
};