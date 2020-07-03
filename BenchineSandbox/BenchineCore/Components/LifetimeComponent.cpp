#include "BenchinePCH.h"
#include "Components/LifetimeComponent.h"

LifetimeComponent::LifetimeComponent(float lifeTime)
    : m_LifeTime(lifeTime)
{

}

void LifetimeComponent::Initialize()
{

}

void LifetimeComponent::Update(float dT)
{
    m_LifeTime -= dT;

    if (m_LifeTime < 0)
    {
        GetGameObject()->MarkForDelete();
    }
}