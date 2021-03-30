#pragma once
#include <string>
#include "Core/Memory.hpp"
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
		return new Font(fullPath, 32);
	}
};

class Texture2D;
class TextureLoader final : public ResourceLoader<Texture2D>
{
public:
	Texture2D* Load(const std::string& filePath) override
	{
		const auto fullPath = m_DataPath + filePath;
		return new Texture2D(fullPath);
	}
};

class SoundByte;
class SoundByteLoader final : public ResourceLoader<SoundByte>
{
public:
	SoundByte* Load(const std::string& filePath) override
	{
		const auto fullPath = m_DataPath + filePath;
		return new SoundByte(fullPath);
	}
};

class SoundStream;
class SoundStreamLoader final : public ResourceLoader<SoundStream>
{
public:
	SoundStream* Load(const std::string& filePath) override
	{
		const auto fullPath = m_DataPath + filePath;
		return new SoundStream(fullPath);
	}
};