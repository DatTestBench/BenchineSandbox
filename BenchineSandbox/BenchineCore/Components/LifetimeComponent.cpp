#include "BenchinePCH.h"
#include "Components/LifetimeComponent.h"

LifetimeComponent::LifetimeComponent(const f32 lifeTime)
	: m_LifeTime(lifeTime)
{
}

void LifetimeComponent::Initialize()
{
}

void LifetimeComponent::Update(const f32 dT)
{
	m_LifeTime -= dT;

	if (m_LifeTime < 0)
	{
		GetGameObject()->MarkForDelete();
	}
}
