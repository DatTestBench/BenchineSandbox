#include "BenchinePCH.h"
#include "Components/SpriteComponent.h"
#include "Components/RenderComponent.h"
#include "Graphics/GLTextureWrapper.h"
SpriteComponent::SpriteComponent(Texture2D* pSpriteSheet, uint32_t nrCols, uint32_t nrRows, uint32_t nrZones, float fps)
    : m_pSpriteSheet(pSpriteSheet)
    , m_Cols(nrCols)
    , m_Rows(nrRows)
    , m_Zones(nrZones)
    , m_Fps(fps)
    , m_CurrentElapsed()
    , m_CurrentFrame()
    , m_CurrentZone(0)
{

}

void SpriteComponent::Initialize()
{
    IRect src{};
    src.Width = GetFrameWidth();
    src.Height = GetFrameHeight();

    src.Pos.x = 0; 
    const uint32_t zoneSize = m_Rows / m_Zones;
    src.Pos.y = static_cast<int32_t>(src.Height * ((m_CurrentFrame / m_Cols) + (m_CurrentZone * zoneSize)));

    m_pSpriteSheet->GetTextureWrapper()->SetSource(src);
    GetGameObject()->GetRenderComponent()->AddTexture(m_pSpriteSheet->GetTextureWrapper());
}

void SpriteComponent::Update(float dT)
{
    m_CurrentElapsed += dT;
    if (m_CurrentElapsed >= 1.f / m_Fps)
    {
        ++m_CurrentFrame %= (m_Cols * (m_Rows / m_Zones));
        m_CurrentElapsed -= 1.f / m_Fps;

        IRect src{};
        src.Width = GetFrameWidth();
        src.Height = GetFrameHeight();

        src.Pos.x = static_cast<int32_t>(src.Width * (m_CurrentFrame % m_Cols));

        const uint32_t zoneSize = m_Rows / m_Zones;

        src.Pos.y = static_cast<int32_t>(src.Height * ((m_CurrentFrame / m_Cols) + (m_CurrentZone * zoneSize)));

        m_pSpriteSheet->GetTextureWrapper()->SetSource(src);
    }
    GetGameObject()->GetRenderComponent()->AddTexture(m_pSpriteSheet->GetTextureWrapper());
}

void SpriteComponent::SetCurrentZone(uint32_t zone) noexcept
{
    if (zone > m_Zones)
    {
        DEBUGONLY(Logger::Log<LEVEL_WARNING>("SpriteComponent::SetCurrentZone()") << "Trying to use zone \"" << zone << "\", but the spritesheet only has \"" << m_Zones << "\nzones (defaulting to using last zone on sheet)"); 
        m_CurrentZone = m_Zones;
    }
    else
    {
        m_CurrentZone = zone;
    }
}

void SpriteComponent::AddAnimation(const std::string& name, uint32_t zone) noexcept
{
    m_AnimationMap.emplace(std::pair(name, zone));
}

void SpriteComponent::SetAnimation(const std::string& name) noexcept
{
    m_CurrentZone = m_AnimationMap.at(name);
}