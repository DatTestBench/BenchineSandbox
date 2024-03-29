#pragma once
#include "Components/BaseComponent.h"
#include "Resources/Texture2D.h"
class TextureComponent final : public BaseComponent
{
public:
	explicit TextureComponent(Texture2D* pTexture);

	void Update(f32 dT) override;

	/**
	 * Getter
	 * @return SpritesheetTexture
	 * */
	[[nodiscard]] auto GetTextureWrapper() const noexcept -> GLTextureWrapper* { return m_pTexture->GetTextureWrapper(); }

protected:
	void Initialize() override;

private:
	Texture2D* m_pTexture;
};
