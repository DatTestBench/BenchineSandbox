#pragma once
//struct Mix_Music;
class SoundStream
{
public:
    explicit SoundStream(const std::string& fullPath);
    ~SoundStream();
    DEL_ROF(SoundStream)

    void Play(bool shouldRepeat) const noexcept;
    static void Stop() noexcept;
    static void Pause() noexcept;
    static void Resume() noexcept;
    static void SetVolume(uint32_t volume) noexcept;
    static auto GetVolume()noexcept-> int;

private:
    Mix_Music* m_pMixMusic;
};