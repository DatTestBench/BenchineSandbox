#pragma once

struct _TTF_Font;
class GLTextureWrapper;
class Font
{
public:
	explicit Font(const std::string& fullPath, uint32_t size);
	~Font();
	DEL_ROF(Font)
	[[nodiscard]] constexpr auto GetFont() const noexcept-> _TTF_Font* { return m_pFont; }
	[[nodiscard]] constexpr auto GetTextureWrapper() const noexcept-> GLTextureWrapper* { return m_pTexture; }
	GLTextureWrapper* GenerateFontTexture(const std::string& text, const SDL_Color& color);


private:
	_TTF_Font* m_pFont;
	GLTextureWrapper* m_pTexture;
};

