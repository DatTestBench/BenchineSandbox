#include "Components/FPSComponent.h"

void FPSComponent::Initialize()
{
}

void FPSComponent::Update(const f32 dT)
{
	m_FPS = 1.f / dT;
}
