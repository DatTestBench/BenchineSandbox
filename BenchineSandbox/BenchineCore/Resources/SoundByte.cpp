#include "BenchinePCH.h"
#include "Resources/SoundByte.h"

SoundByte::SoundByte(const std::string& fullPath)
	: m_pMixChunk(Mix_LoadWAV(fullPath.c_str()), [](Mix_Chunk* ptr){ Mix_FreeChunk(ptr); ptr = nullptr; })
{
	LOG_CONDITIONAL(m_pMixChunk == nullptr, Error, "Failed to load soundbyte: {0}", Mix_GetError());
}

SoundByte::~SoundByte()
{
}

void SoundByte::Play(const u32 repeats) const
{
	if (m_pMixChunk)
	{
		if (Mix_PlayChannel(-1, m_pMixChunk.get(), repeats) == -1)
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
	if (m_pMixChunk)
	{
		Mix_VolumeChunk(m_pMixChunk.get(), volume);
	}
	else
	{
		LOG(Warning, "SoundByte is nullptr");
	}
}

auto SoundByte::GetVolume() const noexcept -> i32
{
	if (m_pMixChunk)
	{
		return Mix_VolumeChunk(m_pMixChunk.get(), -1);
	}
	else
	{
		LOG(Warning, "SoundByte is nullptr");
		return -1;
	}
}
