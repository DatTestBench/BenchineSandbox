#include "BenchinePCH.h"

#include "Components/TextComponent.h"
#include "Graphics/Renderer.h"
#include "Resources/Font.h"
#include "Resources/Texture2D.h"
#include "Components/TransformComponent.h"
#include "Components/RenderComponent.h"
#include "Scene/GameObject.h"

TextComponent::TextComponent(const std::string& text, Font* font)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_pFont(font)
	, m_Color(SDL_Color{ 255, 255, 255 , 255 })
	, m_pTexture(nullptr)
{
	m_pTexture = m_pFont->GenerateFontTexture(m_Text, m_Color);
}

TextComponent::~TextComponent()
{
}

void TextComponent::Initialize()
{

}

void TextComponent::Update([[maybe_unused]] float dT)
{
	if (m_NeedsUpdate)
	{

		auto offsetMode = m_pTexture->GetOffsetMode();
		auto positionOffset = m_pTexture->GetPositionOffset();
		auto renderPriority = m_pTexture->GetRenderPriority();

		m_pTexture = m_pFont->GenerateFontTexture(m_Text, m_Color);

		m_pTexture->SetOffsetMode(offsetMode);
		m_pTexture->SetPositionOffset(positionOffset);
		m_pTexture->SetRenderPriority(renderPriority);

		m_NeedsUpdate = false;
	}
	GetGameObject()->GetRenderComponent()->AddTexture(m_pTexture);
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text) noexcept
{
	m_Text = text;
	m_NeedsUpdate = true;
}



