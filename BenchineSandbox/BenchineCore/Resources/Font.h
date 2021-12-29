#pragma once
#include <memory>
#include <SDL_pixels.h>
#include <string>

#include "Core/CoreBasicTypes.hpp"
#include "Core/CoreMacros.hpp"
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

	[[nodiscard]] auto GetFont() const noexcept -> _TTF_Font* { return m_pFont.get(); }
	[[nodiscard]] auto GetTextureWrapper() const noexcept -> GLTextureWrapper* { return m_pTexture.get(); }
	GLTextureWrapper* GenerateFontTexture(const std::string& text, const SDL_Color& color);

private:
	std::unique_ptr<_TTF_Font, void(*)(_TTF_Font*)> m_pFont;
	std::unique_ptr<GLTextureWrapper> m_pTexture;
};
