#pragma once

class GLTextureWrapper;
class Texture2D
{
public:
	/**
	 * \brief Wrapper around GLTextureWrapper
	 * \param fullPath Texture file path
	 */
	explicit Texture2D(const std::string& fullPath);
	~Texture2D();
	DEL_ROF(Texture2D)

	[[nodiscard]] auto GetTextureWrapper() const noexcept -> GLTextureWrapper* { return m_pTexture.get(); }
private:
	std::unique_ptr<GLTextureWrapper> m_pTexture;
};

