#pragma once
struct Mix_Chunk;
class SoundByte
{
public:
    explicit SoundByte(const std::string& fullPath);
    ~SoundByte();
    DEL_ROF(SoundByte)

    void Play(uint32_t repeats = 0U) const;
    void SetVolume(uint32_t volume) const;
    [[nodiscard]] constexpr auto GetVolume() const noexcept-> int;
private:
    Mix_Chunk* m_pMixChunk;
};

