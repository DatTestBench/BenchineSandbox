#include "Graphics/Renderer.h"

#include <GL/GLU.h>

#include "Core/Benchine.h"

#include "Debugging/Logger.hpp"

#include "Graphics/GLTextureWrapper.h"

#include "ImGui/imgui_impl_opengl2.h"
#include "ImGui/imgui_impl_sdl.h"

#include "ImNodes/imnodes.h"
Renderer::~Renderer()
{
	Cleanup();
}

void Renderer::Initialize(const WindowSettings& windowSettings)
{
	// OpenGL versions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Window creation
	m_pWindow = SDL_CreateWindow(
		windowSettings.Name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowSettings.Width,
		windowSettings.Height,
		SDL_WINDOW_OPENGL);

	LOG_CONDITIONAL(m_pWindow == nullptr, Error, "SDL_CreateWindow Error: {0}", SDL_GetError());

	// Create OpenGL context 
	m_pContext = SDL_GL_CreateContext(m_pWindow);

	LOG_CONDITIONAL(m_pContext == nullptr, Error, "SDL_GL_CreateContext Error: {0}", SDL_GetError());

	// Set the swap interval for the current OpenGL context,
	// synchronize it with the vertical retrace
	if (m_WindowSettings.EnableVSync)
	{
		LOG_CONDITIONAL(SDL_GL_SetSwapInterval(1) < 0, Error, "SDL_GL_SetSwapInterval Error: {0}", SDL_GetError());
	}
	else
	{
		LOG_CONDITIONAL(SDL_GL_SetSwapInterval(0) < 0, Error, "SDL_GL_SetSwapInterval Error: {0}", SDL_GetError());
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, m_WindowSettings.Width, 0, m_WindowSettings.Height); // y from bottom to top
	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, static_cast<i32>(m_WindowSettings.Width), static_cast<i32>(m_WindowSettings.Height));

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glAlphaFunc(GL_GREATER, 0.5f);
	glEnable(GL_ALPHA_TEST);

	glEnable(GL_DEPTH_TEST);
	SDL_GL_MakeCurrent(m_pWindow, m_pContext);

	ImGui::CreateContext();
	ImNodes::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_pWindow, m_pContext);
	ImGui_ImplOpenGL2_Init();
}

void Renderer::SetupRender() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();
}

void Renderer::PresentRender() const
{
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(m_pWindow);
}

void Renderer::Cleanup()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImNodes::DestroyContext();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(m_pContext);
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
}

void Renderer::RenderTexture(const GLTextureWrapper* pTexture, const glm::vec2& pos, const glm::vec2& scale)
{
	if (!pTexture->IsCreationOk())
	{
		return;
	}

	const auto vertexBuffer = CreateRenderParams(pTexture);

	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0.f);
	glScalef(scale.x, scale.y, 1.f);

	// Tell opengl which texture we will use
	glBindTexture(GL_TEXTURE_2D, pTexture->GetId());
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// Draw
	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS);
		{
			for (auto [uv, vertexPos] : vertexBuffer)
			{
				glTexCoord2f(uv.x, uv.y);
				glVertex3f(vertexPos.x, vertexPos.y, 1.f - 1.f / static_cast<GLfloat>(pTexture->GetRenderPriority()));
			}
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

std::array<VertexUV, 4> Renderer::CreateRenderParams(const GLTextureWrapper* pTexture)
{
	const auto textureWidth = pTexture->GetWidth();
	const auto textureHeight = pTexture->GetHeight();

	const auto renderWidth = pTexture->GetRenderWidth();
	const auto renderHeight = pTexture->GetRenderHeight();

	const auto targetPos = pTexture->GetPositionOffset();

	// Determine the texturecoordinates that should be rendered;
	f32 uvLeft, uvRight, uvTop, uvBottom;

	if (auto source = pTexture->GetSource())
	{
		const auto [pos, width, height] = source.value();
		// Convert to the range [0.0, 1.0]
		uvLeft = static_cast<f32>(pos.x) / static_cast<f32>(textureWidth);
		uvRight = static_cast<f32>(pos.x + width) / static_cast<f32>(textureWidth);
		uvTop = static_cast<f32>(pos.y) / static_cast<f32>(textureHeight);
		uvBottom = static_cast<f32>(pos.y + height) / static_cast<f32>(textureHeight);
	}
	else
	{
		// Use complete texture
		uvLeft = 0.0f;
		uvRight = 1.0f;
		uvTop = 0.0f;
		uvBottom = 1.0f;
	}

	f32 vertexLeft{}, vertexBottom{}, vertexRight{}, vertexTop{};

	switch (pTexture->GetOffsetMode())
	{
	case TextureOffsetMode::Center:
		vertexLeft = targetPos.x - renderWidth / 2.f;
		vertexRight = targetPos.x + renderWidth / 2.f;
		vertexTop = targetPos.y + renderHeight / 2.f;
		vertexBottom = targetPos.y - renderHeight / 2.f;
		break;
	case TextureOffsetMode::Base:
		vertexLeft = targetPos.x - renderWidth / 2.f;
		vertexRight = targetPos.x + renderWidth / 2.f;
		vertexTop = targetPos.y + renderHeight;
		vertexBottom = targetPos.y;
		break;
	case TextureOffsetMode::Top:
		vertexLeft = targetPos.x - renderWidth / 2.f;
		vertexRight = targetPos.x + renderWidth / 2.f;
		vertexTop = targetPos.y;
		vertexBottom = targetPos.y - renderHeight;
		break;
	case TextureOffsetMode::Topleft:
		vertexLeft = targetPos.x;
		vertexRight = targetPos.x + renderWidth;
		vertexTop = targetPos.y;
		vertexBottom = targetPos.y - renderHeight;
		break;
	case TextureOffsetMode::Bottomleft:
		vertexLeft = targetPos.x;
		vertexRight = targetPos.x + renderWidth;
		vertexTop = targetPos.y + renderHeight;
		vertexBottom = targetPos.y;
		break;
	}

	return std::move(std::array
		{
			VertexUV({ uvLeft, uvBottom }, { vertexLeft, vertexBottom }),
			VertexUV({ uvLeft, uvTop }, { vertexLeft, vertexTop }),
			VertexUV({ uvRight, uvTop }, { vertexRight, vertexTop }),
			VertexUV({ uvRight, uvBottom }, { vertexRight, vertexBottom })
		});
}
