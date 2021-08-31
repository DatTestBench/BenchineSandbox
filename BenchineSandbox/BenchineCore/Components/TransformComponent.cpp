#include "Components/TransformComponent.h"
TransformComponent::TransformComponent(const glm::vec3& pos, const glm::vec2& scale)
	: m_Position(pos)
	, m_Scale(scale)
{
}

void TransformComponent::SetPosition(const f32 x, const f32 y, const f32 z) noexcept
{
	// NOTE: in a perfect world this would be `m_Position = {.x = x, .y = y, .z = z};`, but due to nameless union fuckery under the hood this doesn't work with glm
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

void TransformComponent::Update(const f32)
{
}
