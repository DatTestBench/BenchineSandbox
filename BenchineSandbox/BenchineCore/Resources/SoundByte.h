#pragma once
#include <memory>
#include <string>
#include "Core/CoreMacros.hpp"
#include "Core/CoreBasicTypes.hpp"
struct Mix_Chunk;
class SoundByte
{
public:
	/**
     * \brief Wrapper around Mix_Chunk
     * \param fullPath Sound file path 
     */
	explicit SoundByte(const std::string& fullPath);
	~SoundByte();
	DEL_ROF(SoundByte)

	void Play(u32 repeats = 0U) const;
	void SetVolume(u32 volume) const;
	[[nodiscard]] auto GetVolume() const noexcept -> i32;
private:
	std::unique_ptr<Mix_Chunk, void(*)(Mix_Chunk*)> m_pMixChunk;
};
