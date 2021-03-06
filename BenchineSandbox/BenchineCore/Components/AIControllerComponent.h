#pragma once
#include "Components/BaseComponent.h"

enum class AIState
{
	Free,
	Captured
};

class AIControllerComponent final : public BaseComponent
{
public:
	AIControllerComponent();
	virtual ~AIControllerComponent() override = default;
	DEL_ROF(AIControllerComponent)

	void Update(f32 dT) override;
	void InvertDirection();
	void SetDirection(const glm::vec2& direction) { m_Direction = direction; }
	void BubbleHit();

	[[nodiscard]] constexpr auto GetState() const noexcept -> AIState { return m_State; }
	void SetState(const AIState state) noexcept { m_State = state; }

protected:
	void Initialize() override;

private:
	void MoveLeft();
	void MoveRight();
	void Jump();

	glm::vec2 m_Velocity;
	glm::vec2 m_Direction;
	PhysicsComponent2D* m_pPhysicsComponent;

	AIState m_State;

	f32 m_BubbleTimer;
};
