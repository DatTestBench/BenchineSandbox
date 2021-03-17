#include "BenchinePCH.h"
#include "Components/TransformComponent.h"

TransformComponent::TransformComponent()
	: m_Position(0, 0, 1)
	, m_Scale(1, 1)
{
}

void TransformComponent::SetPosition(const f32 x, const f32 y, const f32 z) noexcept
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void TransformComponent::Move(const f32 x, const f32 y, const f32 z) noexcept
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
void TransformComponent::Update([[maybe_unused]] f32 dT)
{
}
