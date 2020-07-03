#include "BenchinePCH.h"
#include "Components/TransformComponent.h"

TransformComponent::TransformComponent()
	: m_Position(0, 0, 1)
	, m_Scale(1, 1)
{

}

void TransformComponent::SetPosition(const float x, const float y, const float z) noexcept
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void TransformComponent::Move(const float x, const float y, const float z) noexcept
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}

void TransformComponent::Move(const glm::vec2& movementVec) noexcept
{
	m_Position.x += movementVec.x;
	m_Position.y += movementVec.y;
}

void TransformComponent::SetScale(const glm::vec2& scale) noexcept
{
	m_Scale = scale;
}

void TransformComponent::Initialize()
{

}
void TransformComponent::Update([[maybe_unused]] float dT)
{

}
