#pragma once
#include "Components/BaseComponent.h"

class GLTextureWrapper;
class Font;
class TextComponent final : public BaseComponent
{
public:

	TextComponent(const std::string& text, Font* font);
	virtual ~TextComponent() override;
	DEL_ROF(TextComponent)

	void Update([[maybe_unused]] float dT) override;

	void SetText(const std::string& text) noexcept;
	void SetColor(const SDL_Color& color) noexcept { m_Color = color; }
	void SetColor(Uint8 r, Uint8 g, Uint8 b) noexcept { m_Color.r = r; m_Color.g = g; m_Color.b = b; }
	[[nodiscard]] constexpr auto GetTexture() const noexcept-> GLTextureWrapper* { return m_pTexture; }


protected:
	void Initialize() override;

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	Font* m_pFont;
	SDL_Color m_Color;
	GLTextureWrapper* m_pTexture;
};

