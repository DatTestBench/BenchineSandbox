#include "BenchinePCH.h"
#include "Resources/ResourceManager.h"

#include <ranges>
#include "Core/Memory.hpp"
#include "Resources/Loaders.h"

ResourceManager::~ResourceManager()
{
	// Interesting: This actually needs to be a reference as otherwise the unique_ptr goes out of scope. Didn't expect that to happen with std::views, thought those would be non owning
	for (auto& pLoader : m_Loaders | std::views::values)
	{
		pLoader->ReleaseResources();
	}
}

void ResourceManager::Initialize(const std::string& dataPath)
{
	// TODO This is also messy. Look for a workaround.
	// Set data-path for all the resource loaders
	BaseLoader::SetDataPath(dataPath);
	// Set data-path for external use
	m_DataPath = dataPath;
	// load support for png and jpg, this takes a while!

	LOG_CONDITIONAL((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG,
					Error, "Failed to load support for pngs: {0}", IMG_GetError());

	LOG_CONDITIONAL((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG,
					Error, "Failed to load support for jpgs: {0}", IMG_GetError());

	LOG_CONDITIONAL(TTF_Init() != 0, Error, "Failed to load support for fonts: {0}", TTF_GetError());

	// load SDL_Mixer support
	LOG_CONDITIONAL(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0,
					Error, "Failed to load support for sound: {0}", Mix_GetError());

	// Initialize Loaders
	AddLoader<Font, FontLoader>();
	AddLoader<Texture2D, TextureLoader>();
	AddLoader<SoundByte, SoundByteLoader>();
	AddLoader<SoundStream, SoundStreamLoader>();
}
