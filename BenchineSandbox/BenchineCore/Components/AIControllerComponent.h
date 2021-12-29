#pragma once
#include "Components/BaseComponent.h"

class PhysicsComponent2D;
class AIControllerComponent final : public BaseComponent
{
public:
	void Update(f32 dT) override;

protected:
	void Initialize() override;

private:
	PhysicsComponent2D* m_pPhysicsComponent = nullptr;
};
