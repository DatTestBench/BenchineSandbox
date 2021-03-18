#include "BenchinePCH.h"
#include "Resources/Font.h"

#include "Core/Memory.hpp"
#include "Graphics/GLTextureWrapper.h"

Font::Font(const std::string& fullPath, const u32 size)
	: m_pFont(TTF_OpenFont(fullPath.c_str(), static_cast<i32>(size)))
	, m_pTexture(nullptr)
{
	LOG_CONDITIONAL(m_pFont == nullptr, Error, "Failed to load font: {0}", TTF_GetError());
}

Font::~Font()
{
	SafeDelete(m_pTexture);
	TTF_CloseFont(m_pFont);
}

GLTextureWrapper* Font::GenerateFontTexture(const std::string& text, const SDL_Color& color)
{
	SafeDelete(m_pTexture);
	const auto pSurface = TTF_RenderText_Blended(m_pFont, text.c_str(), color);

	LOG_CONDITIONAL(pSurface == nullptr, Error, "Surface Invalid: {0}", TTF_GetError());
	
	m_pTexture = new GLTextureWrapper(pSurface);

	SDL_FreeSurface(pSurface);

	return m_pTexture;
}
