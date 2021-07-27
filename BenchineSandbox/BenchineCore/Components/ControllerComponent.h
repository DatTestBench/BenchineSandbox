#pragma once
#include "Components/BaseComponent.h"

enum class MovementDirection
{
	Left,
	Right
};

class ControllerComponent final : public BaseComponent
{
public:
	explicit ControllerComponent(ControllerId playerId);

	void Update(f32 dT) override;

protected:
	void Initialize() override;

private:
	void MoveLeft();
	void MoveRight();
	void Jump();
	glm::vec2 m_Velocity;
	glm::vec2 m_Movement;
	PhysicsComponent2D* m_pPhysicsComponent;
	ControllerId m_PlayerId;
	MovementDirection m_MovementState;
};
