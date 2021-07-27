#include "BenchinePCH.h"
#include "Resources/Texture2D.h"

#include "Core/Memory.hpp"
#include "Graphics/GLTextureWrapper.h"

Texture2D::Texture2D(const std::string& fullPath)
	: m_pTexture(nullptr)
{
	const auto pSurface = IMG_Load(fullPath.c_str());

	LOG_CONDITIONAL(pSurface == nullptr, Error, IMG_GetError());

	m_pTexture = std::make_unique<GLTextureWrapper>(pSurface);
	SDL_FreeSurface(pSurface);
}

// Smart pointer shenanigans, see Font.cpp
Texture2D::~Texture2D() {}
