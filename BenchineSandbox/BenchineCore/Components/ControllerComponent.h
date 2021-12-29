#pragma once
#include <glm/glm.hpp>

#include "Components/BaseComponent.h"

#include "Core/InputManager.h"

enum class MovementDirection
{
	Left,
	Right
};

class PhysicsComponent2D;
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

	glm::vec2 m_Velocity{};
	glm::vec2 m_Movement{};

	MovementDirection m_MovementState = MovementDirection::Right;
	PhysicsComponent2D* m_pPhysicsComponent = nullptr;

	const f32 m_cBaseVelocity = 100.f;
	const f32 m_cGravity = 750.f;
	const f32 m_cFriction = 500.f;

	ControllerId m_PlayerId;
};
