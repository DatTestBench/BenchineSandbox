#include "Components/ControllerComponent.h"

#include <SDL_keycode.h>

#include "Components/PhysicsComponent2D.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h" // TODO: Find a way to not require this include

#include "Core/InputManager.h"

#include "Debugging/Logger.hpp"

#include "Graphics/Renderer.h"

#include "Resources/ResourceManager.h"
#include "Resources/SoundByte.h"

ControllerComponent::ControllerComponent(const ControllerId playerId)
	: m_PlayerId(playerId)
{
}

void ControllerComponent::Initialize()
{
	m_pPhysicsComponent = GetGameObject()->GetComponent<PhysicsComponent2D>();
	LOG_CONDITIONAL(m_pPhysicsComponent == nullptr, Error, "No PhysicsComponent specified, please attach a PhysicsComponent when using a ControllerComponent");

	if (m_PlayerId == ControllerId::Player1)
	{
		INPUT->AddInputBinding(InputBinding("MoveLeft", std::bind(&ControllerComponent::MoveLeft, this), InputState::Down, 'a', -1, GamepadButton::DPAD_LEFT, m_PlayerId));
		INPUT->AddInputBinding(InputBinding("MoveRight", std::bind(&ControllerComponent::MoveRight, this), InputState::Down, 'd', -1, GamepadButton::DPAD_RIGHT, m_PlayerId));
		INPUT->AddInputBinding(InputBinding("Jump", std::bind(&ControllerComponent::Jump, this), InputState::Pressed, 'w', -1, GamepadButton::A, m_PlayerId));
	}
	else if (m_PlayerId == ControllerId::Player2)
	{
		INPUT->AddInputBinding(InputBinding("MoveLeft", std::bind(&ControllerComponent::MoveLeft, this), InputState::Down, SDLK_LEFT, -1, GamepadButton::DPAD_LEFT, m_PlayerId));
		INPUT->AddInputBinding(InputBinding("MoveRight", std::bind(&ControllerComponent::MoveRight, this), InputState::Down, SDLK_RIGHT, -1, GamepadButton::DPAD_RIGHT, m_PlayerId));
		INPUT->AddInputBinding(InputBinding("Jump", std::bind(&ControllerComponent::Jump, this), InputState::Pressed, SDLK_UP, -1, GamepadButton::A, m_PlayerId));
	}
}

void ControllerComponent::Update(const f32 dT)
{
	if (!m_pPhysicsComponent->IsOnGround())
	{
		m_Velocity.y = std::clamp(m_Velocity.y - m_cGravity * dT, -200.f, 1000.f);
	}

	if (abs(m_Velocity.x) > 0.1f)
	{
		m_Velocity.x = m_Velocity.x < 0 ? std::min(m_Velocity.x + m_cFriction * dT, 0.f) : std::max(m_Velocity.x - m_cFriction * dT, 0.f);
	}

	m_Velocity += m_Movement * m_cBaseVelocity;

	m_pPhysicsComponent->SetVelocity(m_Velocity);
	GetTransform()->Move(m_Velocity * dT);

	if (GetTransform()->GetPosition().y < 0.f)
	{
		GetTransform()->SetPosition(GetTransform()->GetPosition().x, static_cast<f32>(RENDERER->GetWindowSettings().Height));
	}
	else if (GetTransform()->GetPosition().y > static_cast<f32>(RENDERER->GetWindowSettings().Height))
	{
		GetTransform()->SetPosition(GetTransform()->GetPosition().x, 0.f);
	}

	m_Movement = { 0, 0 };
}

void ControllerComponent::MoveLeft()
{
	m_Movement.x -= 1;
	m_Velocity.x = 0;

	GetGameObject()->GetComponent<SpriteComponent>()->SetAnimation("RunLeft");
	m_MovementState = MovementDirection::Left;
}

void ControllerComponent::MoveRight()
{
	m_Movement.x += 1;
	m_Velocity.x = 0;
	GetGameObject()->GetComponent<SpriteComponent>()->SetAnimation("RunRight");
	m_MovementState = MovementDirection::Right;
}


void ControllerComponent::Jump()
{
	// todo: fix
	//if (m_pPhysicsComponent->IsOnGround())
	{
		LOG(Info, "Velocity: {0}, {1}", m_Velocity.x, m_Velocity.y);
		m_Velocity.y = 600;
		RESOURCES->Load<SoundByte>("Sounds/Jump.wav")->Play();
	}
}