#include "BenchinePCH.h"
#include "Components/AIControllerComponent.h"
#include "Components/PhysicsComponent2D.h"

AIControllerComponent::AIControllerComponent()
	: m_pPhysicsComponent(nullptr)
{
}

void AIControllerComponent::Initialize()
{
	m_pPhysicsComponent = GetGameObject()->GetComponent<PhysicsComponent2D>();
	LOG_CONDITIONAL(m_pPhysicsComponent == nullptr, Error, "No PhysicsComponent specified, please attach a PhysicsComponent when using a ControllerComponent");
}

void AIControllerComponent::Update(const f32) {}
