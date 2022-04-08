#include "Components/PhysicsComponent2D.h"

#include "TransformComponent.h"
#include "Debugging/DebugRenderer.h"
#include "Scene/Scene.h"
#include <glm/gtx/matrix_transform_2d.hpp>

PhysicsComponent2D::PhysicsComponent2D(const CollisionMode collisionMode)
	: m_CollisionMode(collisionMode)
{
}

void PhysicsComponent2D::Initialize()
{
	switch (m_CollisionMode)
	{
	case CollisionMode::Static:
		GetGameObject()->GetScene()->AddStaticObject(this);
		break;
	case CollisionMode::Dynamic:
		GetGameObject()->GetScene()->AddDynamicObject(this);
		break;
	case CollisionMode::Trigger:
		GetGameObject()->GetScene()->AddTrigger(this);
		break;
	}
}

void PhysicsComponent2D::Update(const f32)
{
	m_IsOnGround = false;
	const auto tMat = translate(glm::mat3(1.f), static_cast<glm::vec2>(GetTransform()->GetPosition()));
	const auto sMat = scale(glm::mat3(1.f), GetTransform()->GetScale());

	const auto transformMat = tMat * sMat;

	// TODO: Try and fix with ranges?
	for (size_t v = 0; v < m_BaseCollider.size(); ++v)
	{
		m_Collider.at(v) = transformMat * glm::vec3(m_BaseCollider.at(v), 1.f);
	}

	DebugRenderer::DrawPolygon(m_Collider);
}

void PhysicsComponent2D::HandleCollision(PhysicsComponent2D* pOtherComponent)
{
	const auto collisionResult = sat::PolygonCollision(this, pOtherComponent);
	if (collisionResult.Intersect)
	{
		switch (m_CollisionMode)
		{
		case CollisionMode::Static:
			m_PhysicsCallback(collisionResult, this, pOtherComponent);
			break;
		case CollisionMode::Dynamic:
			if (!m_CallBackOverriden)
			{
				if (pOtherComponent->GetCollisionMode() == CollisionMode::Static)
				{
					GetTransform()->Move(collisionResult.MinimumTranslationVector);
				}
			}
			m_PhysicsCallback(collisionResult, this, pOtherComponent);
			break;
		case CollisionMode::Trigger:
			m_PhysicsCallback(collisionResult, this, pOtherComponent);
			break;
		}
	}
}
