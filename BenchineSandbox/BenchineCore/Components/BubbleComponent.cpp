#include "BenchinePCH.h"
#include "Components/BubbleComponent.h"
#include "Components/TransformComponent.h"
BubbleComponent::BubbleComponent(const glm::vec2& launchDirection)
    : m_Velocity(launchDirection * 100.f)
{

}

void BubbleComponent::Initialize()
{

}

void BubbleComponent::Update(float dT)
{
    GetTransform()->Move(m_Velocity * dT);
}