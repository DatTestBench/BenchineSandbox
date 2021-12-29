#pragma once
#include <memory>
#include <SDL_mixer.h>
#include <string>

#include "Core/CoreBasicTypes.hpp"
#include "Core/CoreMacros.hpp"

class SoundStream
{
public:
	/**
     * \brief Wrapper around Mix_Music
     * \param fullPath Sound file path
     */
	explicit SoundStream(const std::string& fullPath);
	~SoundStream();
	DEL_ROF(SoundStream)

	void Play(bool shouldRepeat) const noexcept;
	static void Stop() noexcept;
	static void Pause() noexcept;
	static void Resume() noexcept;
	static void SetVolume(u32 volume) noexcept;
	static auto GetVolume() noexcept -> i32;

private:
	std::unique_ptr<Mix_Music, void(*)(Mix_Music*)> m_pMixMusic;
};
