#include "Components/TextComponent.h"
#include "Components/RenderComponent.h"
#include "Graphics/GLTextureWrapper.h"
#include "Resources/Font.h"
TextComponent::TextComponent(const std::string& text, Font* font)
	: m_Text(text)
	, m_pFont(font)
{
	m_pTexture = m_pFont->GenerateFontTexture(m_Text, m_Color);
}

void TextComponent::Initialize()
{
}

void TextComponent::Update([[maybe_unused]] const f32 dT)
{
	if (m_NeedsUpdate)
	{
		const auto offsetMode = m_pTexture->GetOffsetMode();
		const auto positionOffset = m_pTexture->GetPositionOffset();
		const auto renderPriority = m_pTexture->GetRenderPriority();

		m_pTexture = m_pFont->GenerateFontTexture(m_Text, m_Color);

		m_pTexture->SetOffsetMode(offsetMode);
		m_pTexture->SetPositionOffset(positionOffset);
		m_pTexture->SetRenderPriority(renderPriority);

		m_NeedsUpdate = false;
	}
	GetGameObject()->GetRenderComponent()->AddTexture(m_pTexture);
}

void TextComponent::SetText(const std::string& text) noexcept
{
	m_Text = text;
	m_NeedsUpdate = true;
}
