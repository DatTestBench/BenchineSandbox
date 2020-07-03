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
	ControllerComponent(uint32_t playerId);
	virtual ~ControllerComponent() override = default;
	DEL_ROF(ControllerComponent)

	void Update(float dT) override;

	

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
	uint32_t m_PlayerId;
	MovementDirection m_MovementState;
};