#pragma once

#include <optional>
#include <SDL_surface.h>
#include <glm/vec2.hpp>

#include "Core/CoreTypes.hpp"
#include "Core/CoreMacros.hpp"
#include "Helpers/Concepts.hpp"
// Wrapper the OpenGL texture system, to work with SDL_Surface
enum class TextureOffsetMode
{
	Center,
	Base,
	Top,
	Topleft,
	Bottomleft
};

class GLTextureWrapper final
{
public:
	/**
	 * \brief Wrapper around OpenGL textures using SDL_Surfaces
	 * \param pSurface SDL_Surface to use for the texture
	 * \param offsetMode Location offset mode
	 * \param renderPriority "Layer" on the screen where the texture will be displayed, higher priority == closer to the top
	 */
	explicit GLTextureWrapper(const SDL_Surface* pSurface, TextureOffsetMode offsetMode = TextureOffsetMode::Center, u32 renderPriority = 1);
	~GLTextureWrapper();
	DEL_ROF(GLTextureWrapper)

	[[nodiscard]] constexpr auto GetId() const noexcept -> u32 { return m_Id; }
	[[nodiscard]] constexpr auto GetWidth() const noexcept -> u32 { return m_Width; }
	[[nodiscard]] constexpr auto GetHeight() const noexcept -> u32 { return m_Height; }
	[[nodiscard]] constexpr auto GetTargetWidth() const noexcept { return m_TargetWidth; }
	[[nodiscard]] constexpr auto GetTargetHeight() const noexcept { return m_TargetHeight; }
	[[nodiscard]] constexpr auto GetRenderWidth() const noexcept -> u32
	{
		if (m_TargetWidth)
			return m_TargetWidth.value();
		if (m_Source)
			return m_Source.value().Width;
		return m_Width;
	}
	[[nodiscard]] constexpr auto GetRenderHeight() const noexcept -> u32
	{
		if (m_TargetHeight)
			return m_TargetHeight.value();
		if (m_Source)
			return m_Source.value().Height;
		return m_Height;
	}
	
	[[nodiscard]] constexpr auto IsCreationOk() const noexcept -> bool { return m_CreationOk; }

	[[nodiscard]] constexpr auto GetSource() const noexcept { return m_Source; }
	[[nodiscard]] constexpr auto GetRenderPriority() const noexcept -> u32 { return m_RenderPriority; }
	[[nodiscard]] constexpr auto GetOffsetMode() const noexcept -> TextureOffsetMode { return m_OffsetMode; }
	[[nodiscard]] constexpr auto GetPositionOffset() const noexcept -> glm::vec2 { return m_PositionOffset; }

	void SetSource(const IRect& source) noexcept { m_Source = source; }
	void SetTarget(const u32 width, const u32 height) noexcept
	{
		m_TargetWidth = width;
		m_TargetHeight = height;
	}
	
	void SetRenderPriority(const u32 renderPriority) noexcept { m_RenderPriority = renderPriority; }
	void SetOffsetMode(const TextureOffsetMode offsetMode) noexcept { m_OffsetMode = offsetMode; }
	void SetPositionOffset(const glm::vec2& posOffset) noexcept { m_PositionOffset = posOffset; }


private:
	u32 m_Id;

	u32 m_Width;
	u32 m_Height;
	std::optional<u32> m_TargetWidth;
	std::optional<u32> m_TargetHeight;
	std::optional<IRect> m_Source;

	u32 m_RenderPriority;
	glm::vec2 m_PositionOffset;
	TextureOffsetMode m_OffsetMode;

	bool m_CreationOk;
	void CreateTextureFromSurface(const SDL_Surface* pSurface);
};
