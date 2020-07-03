#include "BenchinePCH.h"
#include "Components/AIControllerComponent.h"
#include "Components/PhysicsComponent2D.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Debugging/DebugRenderer.h"
#include <functional>
#include <algorithm>
AIControllerComponent::AIControllerComponent()
	: m_Velocity(0, 0)
	, m_Direction(-1, 0)
	, m_pPhysicsComponent(nullptr)
	, m_BubbleTimer()
	, m_State(AIState::FREE)
{

}

void AIControllerComponent::Initialize()
{
	m_pPhysicsComponent = GetGameObject()->GetComponent<PhysicsComponent2D>();
	if (m_pPhysicsComponent == nullptr)
	{
		DEBUGONLY(Logger::Log<LEVEL_ERROR>("ControllerComponent::Initialize()") << "No PhysicsComponent specified, please attach a PhysicsComponent when using a ControllerComponent");
	}


}

void AIControllerComponent::Update(float dT)
{
	if (m_BubbleTimer > 0)
	{
		m_BubbleTimer-= dT;
	}
	else 
	{
		if (m_State == AIState::CAPTURED)
		{
			m_State = AIState::FREE;
			if (m_Direction.x > 0)
			{
				GetGameObject()->GetComponent<SpriteComponent>()->SetAnimation("RunRight");
			}
				else if (m_Direction.x < 0)
			{
				GetGameObject()->GetComponent<SpriteComponent>()->SetAnimation("RunLeft");
			}
		}


		m_State = AIState::FREE;
		constexpr float velocity = 100.f;
		constexpr float gravity = 750.f;
		constexpr float friction = 500.f;
		if (!m_pPhysicsComponent->IsOnGround())
		{
			m_Velocity.y = std::clamp(m_Velocity.y - gravity * dT, -200.f, 1000.f);
		}

		if (abs(m_Velocity.x) > 0.1f)
		{
			m_Velocity.x = m_Velocity.x < 0 ? std::min(m_Velocity.x + friction * dT, 0.f) : std::max(m_Velocity.x - friction * dT, 0.f);
		}

		m_Velocity += m_Direction * velocity;


		m_Velocity.x = std::clamp(m_Velocity.x, -150.f, 150.f);

    	if (GetTransform()->GetPosition().y < 0.f)
		{
			GetTransform()->SetPosition(GetTransform()->GetPosition().x, static_cast<float>(RENDERER->GetWindowSettings().Height));
		}
		else if (GetTransform()->GetPosition().y > static_cast<float>(RENDERER->GetWindowSettings().Height))
		{
			GetTransform()->SetPosition(GetTransform()->GetPosition().x, 0.f);
		}

		m_pPhysicsComponent->SetVelocity(m_Velocity);
		GetTransform()->Move(m_Velocity * dT);
	}
}

void AIControllerComponent::InvertDirection()
{
	m_Direction.x = -m_Direction.x;

	if (m_Direction.x > 0)
	{
		GetGameObject()->GetComponent<SpriteComponent>()->SetAnimation("RunRight");
	}
	else if (m_Direction.x < 0)
	{
		GetGameObject()->GetComponent<SpriteComponent>()->SetAnimation("RunLeft");
	}

}

void AIControllerComponent::Jump()
{
	m_Velocity.y = 500;
}

void AIControllerComponent::BubbleHit()
{
	m_BubbleTimer = 5.f;
	GetGameObject()->GetComponent<SpriteComponent>()->SetAnimation("Caught");
	m_State = AIState::CAPTURED;
}
