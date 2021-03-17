#pragma once
#include "Components/BaseComponent.h"
#include "Resources/Texture2D.h"
#include "Graphics/GLTextureWrapper.h"
class SpriteComponent final : public BaseComponent
{
public:
	/**
	 * Constructor
	 * @param pSpriteSheet Texture for the spritesheet
	 * @param nrCols Number of columns
	 * @param nrRows Number of rows
	 * @param nrZones Amount of different zones in the spritesheet, to use for different sprites in spritesheets
	 * @param fps Framerate of the animation
	 * */
	SpriteComponent(Texture2D* pSpriteSheet, u32 nrCols, u32 nrRows, u32 nrZones, f32 fps);
	virtual ~SpriteComponent() override = default;
	DEL_ROF(SpriteComponent)

	void Update(f32 dT) override;


	[[nodiscard]] constexpr auto GetFrameWidth() const noexcept -> u32 { return m_pSpriteSheet->GetTextureWrapper()->GetWidth() / m_Cols; }
	[[nodiscard]] constexpr auto GetFrameHeight() const noexcept -> u32 { return m_pSpriteSheet->GetTextureWrapper()->GetHeight() / m_Rows; }
	[[nodiscard]] constexpr auto GetTextureWrapper() const noexcept -> GLTextureWrapper* { return m_pSpriteSheet->GetTextureWrapper(); }

	void SetCurrentZone(u32 zone) noexcept;

	void AddAnimation(const std::string& name, u32 zone) noexcept;
	void SetAnimation(const std::string& name) noexcept;

protected:
	void Initialize() override;

private:
	Texture2D* m_pSpriteSheet;
	u32 m_Cols;
	u32 m_Rows;
	u32 m_Zones;
	u32 m_CurrentZone;

	std::map<std::string, u32> m_AnimationMap;


	f32 m_Fps;
	f32 m_CurrentElapsed;
	u32 m_CurrentFrame;
};
