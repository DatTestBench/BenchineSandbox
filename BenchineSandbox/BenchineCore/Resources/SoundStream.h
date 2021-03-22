#pragma once
//struct Mix_Music;
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
    static auto GetVolume()noexcept -> i32;

private:
    Mix_Music* m_pMixMusic;
};