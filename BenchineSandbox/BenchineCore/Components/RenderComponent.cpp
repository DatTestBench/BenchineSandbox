#include "BenchinePCH.h"
#include "RenderComponent.h"

#include <ranges>

#include "Graphics/Renderer.h"
#include "Scene/GameObject.h"
#include "Components/TransformComponent.h"

RenderComponent::~RenderComponent()
{
	GetGameObject()->GetScene()->RemoveRenderComponent(this);
}

void RenderComponent::Initialize()
{
	GetGameObject()->GetScene()->AddRenderComponent(this);
	GetGameObject()->SetRenderComponent(this);
}

void RenderComponent::Update([[maybe_unused]] const f32 dT)
{
}

void RenderComponent::Render() const
{
	const auto renderPos = GetGameObject()->GetTransform()->GetPosition();
	const auto renderScale = GetGameObject()->GetTransform()->GetScale();
	for (auto texture : m_RenderBuffer | std::views::values)
	{
		Renderer::GetInstance()->RenderTexture(texture, renderPos, renderScale);
	}
}

void RenderComponent::ClearBuffer()
{
	m_RenderBuffer.clear();
}
