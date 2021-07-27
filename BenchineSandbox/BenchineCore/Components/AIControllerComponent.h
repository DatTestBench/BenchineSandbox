// TODO: Remake the AIController component to be a generic, extendable base class with basic interop to the rest of the world
// It should mostly just have an interface to input and output data it can then react to internally (Internal behaviors defined by derived)

#pragma once
#include "Components/BaseComponent.h"

class AIControllerComponent final : public BaseComponent
{
public:
	AIControllerComponent();

	void Update(f32 dT) override;

protected:
	void Initialize() override;

private:
	PhysicsComponent2D* m_pPhysicsComponent;
};
