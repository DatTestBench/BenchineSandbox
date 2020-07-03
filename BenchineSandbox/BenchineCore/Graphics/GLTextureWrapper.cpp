#include "BenchinePCH.h"
#include "GLTextureWrapper.h"

GLTextureWrapper::GLTextureWrapper(SDL_Surface* pSurface, TextureOffsetMode offsetMode, uint32_t renderPriority)
	: m_Id()
	, m_Width()
	, m_Height()
	, m_TargetWidth()
	, m_TargetHeight()
	, m_Source()
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
void GLTextureWrapper::CreateTextureFromSurface(SDL_Surface* pSurface)
{
	m_CreationOk = true;

	//Get image dimensions
	m_Width = static_cast<uint32_t>(pSurface->w);
	m_Height = static_cast<uint32_t>(pSurface->h);

	// Get pixel format information and translate to OpenGl format
	GLenum pixelFormat = GL_RGB;
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
		DEBUGONLY(Logger::Log<LEVEL_ERROR>("GLTextureWrapper::CreateTextureFromSurface()") << " Unknown pixel format, BytesPerPixel " << pSurface->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.");
		//std::cerr << "Texture::CreateFromSurface, unknow pixel format, BytesPerPixel: " << pSurface->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.\n";
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
		DEBUGONLY(Logger::Log<LEVEL_ERROR>("GLTextureWrapper::CreateTextureFromSurface()") << "Error Binding Texture, Error ID: " << e);
		DEBUGONLY(Logger::Log<LEVEL_INFO>("GLTextureWrapper::CreateTextureFromSurface()") << "Can happen if a texture is created before performing the initialization code (e.g. a static Texture object).\n"
			<< "There  might be a white rectangle instead of the image.");

		/*std::cerr << "Texture::CreateFromSurface, error binding textures, Error id = " << e << '\n';
		std::cerr << "Can happen if a texture is created before performing the initialization code (e.g. a static Texture object).\n";
		std::cerr << "There might be a white rectangle instead of the image.\n";*/
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