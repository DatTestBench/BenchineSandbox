#pragma once
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
    [[nodiscard]] constexpr auto GetVolume() const noexcept -> i32;
private:
    Mix_Chunk* m_pMixChunk;
};

