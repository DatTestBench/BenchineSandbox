#include "BenchinePCH.h"
#include "Resources/Texture2D.h"
#include "Graphics/GLTextureWrapper.h"
Texture2D::Texture2D(const std::string& fullPath)
	: m_pTexture(nullptr)
{
	const auto pSurface = IMG_Load(fullPath.c_str());

	if (pSurface == nullptr)
	{
		DEBUGONLY(Logger::Log<LEVEL_ERROR>("Texture2D::Texture2D()") << IMG_GetError());
	}

	m_pTexture = new GLTextureWrapper(pSurface);
	SDL_FreeSurface(pSurface);
}

Texture2D::~Texture2D()
{
	SafeDelete(m_pTexture);
}
