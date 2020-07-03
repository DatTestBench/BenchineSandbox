#pragma once
// Wrapper the OpenGL texture system, to work with SDL_Surface
#include "Helpers/GeneralHelpers.h"

enum class TextureOffsetMode
{
	CENTER,
	BASE,
	TOP,
	TOPLEFT,
	BOTTOMLEFT
};

class GLTextureWrapper final
{
public:
	GLTextureWrapper(SDL_Surface* pSurface, TextureOffsetMode offsetMode = TextureOffsetMode::CENTER, uint32_t renderPriority = 1);
	~GLTextureWrapper();
	DEL_ROF(GLTextureWrapper)

	[[nodiscard]] constexpr auto GetId() const noexcept-> GLuint { return m_Id; }
	[[nodiscard]] constexpr auto GetWidth() const noexcept-> uint32_t { return m_Width; }
	[[nodiscard]] constexpr auto GetHeight() const noexcept-> uint32_t { return m_Height; }
	[[nodiscard]] constexpr auto GetTargetWidth() const noexcept-> float { return m_TargetWidth; }
	[[nodiscard]] constexpr auto GetTargetHeight() const noexcept-> float { return m_TargetHeight; }
	[[nodiscard]] constexpr auto IsCreationOk() const noexcept-> bool { return m_CreationOk; }

	[[nodiscard]] constexpr auto GetSource() const noexcept-> const IRect& { return m_Source; }
	[[nodiscard]] constexpr auto GetRenderPriority() const noexcept-> uint32_t { return m_RenderPriority; }
	[[nodiscard]] constexpr auto GetOffsetMode() const noexcept-> TextureOffsetMode { return m_OffsetMode; }
	[[nodiscard]] constexpr auto GetPositionOffset() const noexcept-> glm::vec2 { return m_PositionOffset; }

	void SetSource(const IRect& source) noexcept { m_Source = source; }
	void SetTarget(const float width, const float height) noexcept { m_TargetWidth = width; m_TargetHeight = height; }
	void SetTarget(const uint32_t width, const uint32_t height) noexcept { m_TargetWidth = static_cast<float>(width); m_TargetHeight = static_cast<float>(height); }
	void SetRenderPriority(uint32_t renderPriority) noexcept { m_RenderPriority = renderPriority; }
	void SetOffsetMode(TextureOffsetMode offsetMode) noexcept { m_OffsetMode = offsetMode; }
	void SetPositionOffset(const glm::vec2& posOffset) noexcept { m_PositionOffset = posOffset; }


private:
	GLuint m_Id;

	uint32_t m_Width;
	uint32_t m_Height;
	float m_TargetWidth;
	float m_TargetHeight;
	IRect m_Source;

	uint32_t m_RenderPriority;
	glm::vec2 m_PositionOffset;
	TextureOffsetMode m_OffsetMode;

	bool m_CreationOk;
	void CreateTextureFromSurface(SDL_Surface* pSurface);
};