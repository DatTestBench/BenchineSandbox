#pragma once
#include "Components/BaseComponent.h"

enum class AIState
{
	FREE,
	CAPTURED
};

class AIControllerComponent final : public BaseComponent
{
public:
	AIControllerComponent();
	virtual ~AIControllerComponent() override = default;
	DEL_ROF(AIControllerComponent)

	void Update(float dT) override;
	void InvertDirection();
    void SetDirection (const glm::vec2& direction) { m_Direction = direction; }
	void BubbleHit();

	[[nodiscard]] constexpr auto GetState() const noexcept-> AIState { return m_State; }
	void SetState(AIState state) noexcept { m_State = state; }

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

	float m_BubbleTimer;

};