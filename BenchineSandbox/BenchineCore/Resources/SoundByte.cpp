#include "BenchinePCH.h"
#include "Resources/SoundByte.h"

SoundByte::SoundByte(const std::string& fullPath)
	: m_pMixChunk(Mix_LoadWAV(fullPath.c_str()))
{
	LOG_CONDITIONAL(m_pMixChunk == nullptr, Error, "Failed to load soundbyte: {0}", Mix_GetError());
}

SoundByte::~SoundByte()
{
	Mix_FreeChunk(m_pMixChunk);
	m_pMixChunk = nullptr;
}

void SoundByte::Play(const u32 repeats) const
{
	if (m_pMixChunk != nullptr)
	{
		if (Mix_PlayChannel(-1, m_pMixChunk, repeats) == -1)
		{
			LOG(Warning, "No free channel available to play sound");
		}
	}
	else
	{
		LOG(Warning, "SoundByte is nullptr");
	}
}

void SoundByte::SetVolume(const u32 volume) const
{
	if (m_pMixChunk != nullptr)
	{
		Mix_VolumeChunk(m_pMixChunk, volume);
	}
	else
	{
		LOG(Warning, "SoundByte is nullptr");
	}
}

constexpr auto SoundByte::GetVolume() const noexcept -> i32
{
	if (m_pMixChunk != nullptr)
	{
		return Mix_VolumeChunk(m_pMixChunk, -1);
	}
	else
	{
		LOG(Warning, "SoundByte is nullptr");
		return -1;
	}
}
