#pragma once
#include "Components/BaseComponent.h"

enum class MovementDirection
{
	LEFT,
	RIGHT
};


class ControllerComponent final : public BaseComponent
{
public:
	ControllerComponent(u32 playerId);
	virtual ~ControllerComponent() override = default;
	DEL_ROF(ControllerComponent)

	void Update(f32 dT) override;



protected:
	void Initialize() override;

private:
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Shoot();
	glm::vec2 m_Velocity;
	glm::vec2 m_Movement;
	PhysicsComponent2D* m_pPhysicsComponent;
	u32 m_PlayerId;
	MovementDirection m_MovementState;
};
