#include "BenchinePCH.h"
#include "Resources/SoundByte.h"

SoundByte::SoundByte(const std::string& fullPath)
    : m_pMixChunk(Mix_LoadWAV(fullPath.c_str()))
{
    if (m_pMixChunk == nullptr)
    {
        DEBUGONLY(Logger::Log<LEVEL_ERROR>("SoundByte::SoundByte()") << "Failed to load soundbyte " << Mix_GetError());
    }
}

SoundByte::~SoundByte()
{
    Mix_FreeChunk(m_pMixChunk);
    m_pMixChunk = nullptr;
}

void SoundByte::Play(uint32_t repeats) const
{
    if (m_pMixChunk != nullptr)
    {
        if (Mix_PlayChannel(-1, m_pMixChunk, repeats) == -1)
        {
            DEBUGONLY(Logger::Log<LEVEL_WARNING>("SoundByte::Play()") << "No free channel available to play sound");
        }
    }
    else
    {
        DEBUGONLY(Logger::Log<LEVEL_WARNING>("SoundByte::Play()") << "SoundByte is nullptr");
    }
}

void SoundByte::SetVolume(uint32_t volume) const
{
    if (m_pMixChunk != nullptr)
    {
        Mix_VolumeChunk(m_pMixChunk, volume);
    }
    else
    {
        DEBUGONLY(Logger::Log<LEVEL_WARNING>("SoundByte::Play()") << "SoundByte is nullptr");
    }
}

[[nodiscard]] constexpr auto SoundByte::GetVolume() const noexcept-> int
{
    if (m_pMixChunk != nullptr)
    {
        return Mix_VolumeChunk(m_pMixChunk, -1);
    }
    else
    {
        DEBUGONLY(Logger::Log<LEVEL_WARNING>("SoundByte::Play()") << "SoundByte is nullptr");
        return -1;
    }
}