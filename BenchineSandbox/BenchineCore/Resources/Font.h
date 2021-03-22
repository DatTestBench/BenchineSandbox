#pragma once

struct _TTF_Font;
class GLTextureWrapper;
class Font
{
public:
	/**
	 * \brief Wrapper around TTF_Fonts
	 * \param fullPath Path to the font file
	 * \param size Font size
	 */
	explicit Font(const std::string& fullPath, u32 size);
	~Font();
	DEL_ROF(Font)
	[[nodiscard]] constexpr auto GetFont() const noexcept -> _TTF_Font* { return m_pFont; }
	[[nodiscard]] constexpr auto GetTextureWrapper() const noexcept -> GLTextureWrapper* { return m_pTexture; }
	GLTextureWrapper* GenerateFontTexture(const std::string& text, const SDL_Color& color);

private:
	_TTF_Font* m_pFont;
	GLTextureWrapper* m_pTexture;
};

