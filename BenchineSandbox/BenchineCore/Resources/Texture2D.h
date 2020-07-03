#pragma once

// Wrapper around the GLTextureWrapper
class GLTextureWrapper;
class Texture2D
{
public:
	explicit Texture2D(const std::string& fullPath);
	~Texture2D();
	DEL_ROF(Texture2D)

	[[nodiscard]] constexpr auto GetTextureWrapper() const noexcept-> GLTextureWrapper* { return m_pTexture; }


private:
	GLTextureWrapper* m_pTexture;
};

