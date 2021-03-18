#include "BenchinePCH.h"
#include "Components/FPSComponent.h"

FPSComponent::FPSComponent()
	: m_FPS()
{
}

void FPSComponent::Initialize()
{
}

void FPSComponent::Update([[maybe_unused]] const f32 dT)
{
	m_FPS = 1.f / dT;
}
