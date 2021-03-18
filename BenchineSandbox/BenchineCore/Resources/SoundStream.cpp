#include "BenchinePCH.h"
#include "Resources/SoundStream.h"

SoundStream::SoundStream(const std::string& fullPath)
	: m_pMixMusic(Mix_LoadMUS(fullPath.c_str()))
{

	LOG_CONDITIONAL(m_pMixMusic == nullptr, Error, "Failed to load soundstream: {0}", Mix_GetError());
}

SoundStream::~SoundStream()
{
	Mix_FreeMusic(m_pMixMusic);
	m_pMixMusic = nullptr;
}

void SoundStream::Play(const bool shouldRepeat) const noexcept
{
	if (m_pMixMusic != nullptr)
	{
		if (Mix_PlayMusic(m_pMixMusic, shouldRepeat ? -1 : 1))
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
auto SoundStream::GetVolume() noexcept -> i32
{
	return Mix_VolumeMusic(-1);
}
