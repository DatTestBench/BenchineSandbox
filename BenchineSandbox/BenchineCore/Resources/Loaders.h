#pragma once
#include <string>
#include "Resources/ResourceLoader.h"

/*Resource Types*/
#include "Resources/Font.h"
#include "Resources/Texture2D.h"
#include "Resources/SoundByte.h"
#include "Resources/SoundStream.h"

class Font;
class FontLoader final : public ResourceLoader<Font>
{
public:
	Font* Load(const std::string& filePath) override
	{
		const auto fullPath = m_DataPath + filePath;
		Font* pFont = new Font(fullPath, 32);
		
		return pFont;
	}

	void Release(Font* pResource) override
	{
		SafeDelete(pResource);
	}
};

class Texture2D;
class TextureLoader final : public ResourceLoader<Texture2D>
{
public:
	Texture2D* Load(const std::string& filePath) override
	{
		const auto fullPath = m_DataPath + filePath;
		Texture2D* pTexture = new Texture2D(fullPath);

		return pTexture;
	}

	void Release(Texture2D* pResource) override
	{
		SafeDelete(pResource);
	}
};

class SoundByte;
class SoundByteLoader final : public ResourceLoader<SoundByte>
{
public:
	SoundByte* Load(const std::string& filePath) override
	{
		const auto fullPath = m_DataPath + filePath;
		SoundByte* pSoundByte = new SoundByte(fullPath);

		return pSoundByte;
	}

	void Release(SoundByte* pSoundByte) override
	{
		SafeDelete(pSoundByte);
	}
};

class SoundStream;
class SoundStreamLoader final : public ResourceLoader<SoundStream>
{
public:
	SoundStream* Load(const std::string& filePath) override
	{
		const auto fullPath = m_DataPath + filePath;
		SoundStream* pSoundStream = new SoundStream(fullPath);

		return pSoundStream;
	}

	void Release(SoundStream* pSoundStream) override
	{
		SafeDelete(pSoundStream);
	}
};