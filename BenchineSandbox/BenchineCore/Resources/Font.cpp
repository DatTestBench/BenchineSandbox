#include "BenchinePCH.h"
#include "Resources/Font.h"

#include "Core/Memory.hpp"
#include "Graphics/GLTextureWrapper.h"

Font::Font(const std::string& fullPath, const u32 size)
	: m_pFont(TTF_OpenFont(fullPath.c_str(), static_cast<i32>(size)), [](_TTF_Font* ptr){ TTF_CloseFont(ptr); ptr = nullptr; })
	, m_pTexture(nullptr)
{
	LOG_CONDITIONAL(m_pFont == nullptr, Error, "Failed to load font: {0}", TTF_GetError());
}

// Interesting: this destructor needs to be here. If the destructor = default, m_pTexture's default destructor will not compile.
// https://stackoverflow.com/questions/6012157/is-stdunique-ptrt-required-to-know-the-full-definition-of-t
// https://stackoverflow.com/questions/13414652/forward-declaration-with-unique-ptr
Font::~Font()
{
}

GLTextureWrapper* Font::GenerateFontTexture(const std::string& text, const SDL_Color& color)
{
	const auto pSurface = TTF_RenderText_Blended(m_pFont.get(), text.c_str(), color);

	LOG_CONDITIONAL(pSurface == nullptr, Error, "Surface Invalid: {0}", TTF_GetError());
	
	m_pTexture.reset(new GLTextureWrapper(pSurface));

	SDL_FreeSurface(pSurface);

	return m_pTexture.get();
}
