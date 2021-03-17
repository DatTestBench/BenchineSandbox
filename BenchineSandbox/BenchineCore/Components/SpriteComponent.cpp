#include "BenchinePCH.h"
#include "Components/SpriteComponent.h"
#include "Components/RenderComponent.h"
#include "Graphics/GLTextureWrapper.h"

SpriteComponent::SpriteComponent(Texture2D* pSpriteSheet, const u32 nrCols, const u32 nrRows, const u32 nrZones, const f32 fps)
	: m_pSpriteSheet(pSpriteSheet)
	, m_Cols(nrCols)
	, m_Rows(nrRows)
	, m_Zones(nrZones)
	, m_CurrentZone(0)
	, m_Fps(fps)
	, m_CurrentElapsed()
	, m_CurrentFrame()
{
}

void SpriteComponent::Initialize()
{
	IRect src{};
	src.Width = GetFrameWidth();
	src.Height = GetFrameHeight();

	src.Pos.x = 0;
	const u32 zoneSize = m_Rows / m_Zones;
	src.Pos.y = static_cast<u32>(src.Height * ((m_CurrentFrame / m_Cols) + (m_CurrentZone * zoneSize)));

	m_pSpriteSheet->GetTextureWrapper()->SetSource(src);
	GetGameObject()->GetRenderComponent()->AddTexture(m_pSpriteSheet->GetTextureWrapper());
}

void SpriteComponent::Update(const f32 dT)
{
	m_CurrentElapsed += dT;
	if (m_CurrentElapsed >= 1.f / m_Fps)
	{
		++m_CurrentFrame %= (m_Cols * (m_Rows / m_Zones));
		m_CurrentElapsed -= 1.f / m_Fps;

		IRect src{};
		src.Width = GetFrameWidth();
		src.Height = GetFrameHeight();

		src.Pos.x = static_cast<i32>(src.Width * (m_CurrentFrame % m_Cols));

		const u32 zoneSize = m_Rows / m_Zones;

		src.Pos.y = static_cast<i32>(src.Height * ((m_CurrentFrame / m_Cols) + (m_CurrentZone * zoneSize)));

		m_pSpriteSheet->GetTextureWrapper()->SetSource(src);
	}
	GetGameObject()->GetRenderComponent()->AddTexture(m_pSpriteSheet->GetTextureWrapper());
}

void SpriteComponent::SetCurrentZone(u32 zone) noexcept
{
	if (zone > m_Zones)
	{
		LOG(LEVEL_WARNING, "Trying to use zone {0}, but the spritesheet only has {1} zones (defaulting to last zone on sheet)", zone, m_Zones);
		m_CurrentZone = m_Zones;
	}
	else
	{
		m_CurrentZone = zone;
	}
}

void SpriteComponent::AddAnimation(const std::string& name, u32 zone) noexcept
{
	m_AnimationMap.emplace(std::pair(name, zone));
}

void SpriteComponent::SetAnimation(const std::string& name) noexcept
{
	m_CurrentZone = m_AnimationMap.at(name);
}
