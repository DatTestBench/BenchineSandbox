#include "Graphics/GLTextureWrapper.h"

#include <SDL_opengl.h>

#include "Debugging/Logger.hpp"
GLTextureWrapper::GLTextureWrapper(const SDL_Surface* pSurface, const TextureOffsetMode offsetMode, const u32 renderPriority)
	: m_Id()
	, m_Width()
	, m_Height()
	, m_RenderPriority(renderPriority)
	, m_PositionOffset()
	, m_OffsetMode(offsetMode)
	, m_CreationOk(false)
{
	CreateTextureFromSurface(pSurface);
}

GLTextureWrapper::~GLTextureWrapper()
{
	glDeleteTextures(1, &m_Id);
}

//https://geometrian.com/programming/tutorials/texturegl/index.php
void GLTextureWrapper::CreateTextureFromSurface(const SDL_Surface* pSurface)
{
	m_CreationOk = true;

	//Get image dimensions
	m_Width = static_cast<u32>(pSurface->w);
	m_Height = static_cast<u32>(pSurface->h);

	// Get pixel format information and translate to OpenGl format
	GLenum pixelFormat;
	switch (pSurface->format->BytesPerPixel)
	{
	case 3:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGB;
		}
		else
		{
			pixelFormat = GL_BGR;
		}
		break;
	case 4:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGBA;
		}
		else
		{
			pixelFormat = GL_BGRA;
		}
		break;
	default:
		LOG(Error, "Unknown pixel format, {0} bytes per pixel.\nUse 32 bit or 24 bit images.", pSurface->format->BytesPerPixel);
		m_CreationOk = false;
		return;
	}

	//Generate an array of textures.  We only want one texture (one element array), so trick
	//it by treating "texture" as array of length one.
	glGenTextures(1, &m_Id);

	//Select (bind) the texture we just generated as the current 2D texture OpenGL is using/modifying.
	//All subsequent changes to OpenGL's texturing state for 2D textures will affect this texture.
	glBindTexture(GL_TEXTURE_2D, m_Id);
	// check for errors. Can happen if a texture is created while a static pointer is being initialized, even before the call to the main function.
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		LOG(Error, "Error Binding Texture, Error ID: {0}", e);
		LOG(Info, "Can happen if a texture is created before performing the initialization code (e.g. a static Texture object).\nThere  might be a white rectangle instead of the image.");
	}

	// Specify the texture's data.  
	// This function is a bit tricky, and it's hard to find helpful documentation. 
	// A summary:
	//    GL_TEXTURE_2D:    The currently bound 2D texture (i.e. the one we just made)
	//                0:    The mipmap level.  0, since we want to update the base level mipmap image (i.e., the image itself,
	//                         not cached smaller copies)
	//          GL_RGBA:    Specifies the number of color components in the texture.
	//                     This is how OpenGL will store the texture internally (kinda)--
	//                     It's essentially the texture's type.
	//       surface->w:    The width of the texture
	//       surface->h:    The height of the texture
	//                0:    The border.  Don't worry about this if you're just starting.
	//      pixelFormat:    The format that the *data* is in--NOT the texture! 
	// GL_UNSIGNED_BYTE:    The type the data is in.  In SDL, the data is stored as an array of bytes, with each channel
	//                         getting one byte.  This is fairly typical--it means that the image can store, for each channel,
	//                         any value that fits in one byte (so 0 through 255).  These values are to be interpreted as
	//                         *unsigned* values (since 0x00 should be dark and 0xFF should be bright).
	//  surface->pixels:    The actual data.  As above, SDL's array of bytes.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

	// Set the minification and magnification filters.  In this case, when the texture is minified (i.e., the texture's pixels (texels) are
	// *smaller* than the screen pixels you're seeing them on, linearly filter them (i.e. blend them together).  This blends four texels for
	// each sample--which is not very much.  Mipmapping can give better results.  Find a texturing tutorial that discusses these issues
	// further.  Conversely, when the texture is magnified (i.e., the texture's texels are *larger* than the screen pixels you're seeing
	// them on), linearly filter them.  Qualitatively, this causes "blown up" (overmagnified) textures to look blurry instead of blocky.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
