#include "Components/RenderComponent.h"

#include "Components/TransformComponent.h"
#include "Graphics/Renderer.h"
#include "Scene/Scene.h"
#include <ranges>

RenderComponent::~RenderComponent()
{
	GetGameObject()->GetScene()->RemoveRenderComponent(this);
}

void RenderComponent::Initialize()
{
	GetGameObject()->GetScene()->AddRenderComponent(this);
	GetGameObject()->SetRenderComponent(this);
}

void RenderComponent::Update(const f32)
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
