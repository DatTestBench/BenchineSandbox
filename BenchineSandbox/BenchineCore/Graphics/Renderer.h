#pragma once

#include <SDL.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <SDL_opengl.h>

#include "Core/CoreTypes.hpp"
#include "Helpers/Singleton.hpp"


enum class RenderDepth : u32
{
	//Layer furthest back, use for something like distant landscale, walls, ect
	Background = 1U,
	//Second Layer, use for something like level geometry you want the player to move in front of
	MidgroundLayer1 = 2U,
	//Third layer, use for something like objects that should be in front of level geometry, but behind the player
	MidgroundLayer2 = 3U,
	//Fourth layer, use for stuff like players
	PlayerLayer = 4U,
	//Fifth layer, use for foreground objects or level geometry you want to be in front of the player
	ForegroundLayer = 5U
};

struct SDL_Window;
class GLTextureWrapper;
class Renderer final : public Singleton<Renderer>
{
public:
	explicit Renderer(Token)
		: m_pContext(nullptr)
		, m_pWindow(nullptr)
	{
	}
	~Renderer();

	void Initialize(const WindowSettings& windowSettings);
	void SetupRender() const;
	void PresentRender() const;

	[[nodiscard]] constexpr auto GetWindowSettings() const noexcept -> const WindowSettings& { return m_WindowSettings; }

	/**
	 * \brief Render GLTextureWrapper to the screen
	 * \param pTexture Texture to render
	 * \param pos Position
	 * \param scale 2D texture scale
	 */
	static void RenderTexture(const GLTextureWrapper* pTexture, const glm::vec2& pos, const glm::vec2& scale);

private:
	void Cleanup();

	WindowSettings m_WindowSettings;
	SDL_GLContext m_pContext;
	SDL_Window* m_pWindow;

	static std::array<VertexUV, 4> CreateRenderParams(const GLTextureWrapper* pTexture);
};

#define RENDERER Renderer::GetInstance()
