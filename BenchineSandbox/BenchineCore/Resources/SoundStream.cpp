#include "Resources/SoundStream.h"

#include "Debugging/Logger.hpp"

SoundStream::SoundStream(const std::string& fullPath)
	: m_pMixMusic(Mix_LoadMUS(fullPath.c_str()), [] (Mix_Music* ptr)
	{
		Mix_FreeMusic(ptr);
		ptr = nullptr;
	})
{
	LOG_CONDITIONAL(m_pMixMusic == nullptr, Error, "Failed to load soundstream: {0}", Mix_GetError());
}

// Smart pointer shenanigans, see Font.cpp
SoundStream::~SoundStream()
{
}

void SoundStream::Play(const bool shouldRepeat) const noexcept
{
	if (m_pMixMusic != nullptr)
	{
		if (Mix_PlayMusic(m_pMixMusic.get(), shouldRepeat ? -1 : 1))
		{
			LOG(Warning, "Couldn't play music");
		}
	}
	else
	{
		LOG(Warning, "SoundStream is nullptr");
	}
}

void SoundStream::Stop() noexcept
{
	Mix_HaltMusic();
}
void SoundStream::Pause() noexcept
{
	Mix_PauseMusic();
}
void SoundStream::Resume() noexcept
{
	Mix_ResumeMusic();
}
void SoundStream::SetVolume(const u32 volume) noexcept
{
	Mix_VolumeMusic(volume);
}
i32 SoundStream::GetVolume() noexcept
{
	return Mix_VolumeMusic(-1);
}
