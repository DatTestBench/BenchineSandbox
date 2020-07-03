#include "BenchinePCH.h"

#include "Resources/Texture2D.h"
#include "glm/geometric.hpp"
#include "Debugging/DebugRenderer.h"
#include "Graphics/GLTextureWrapper.h"
Renderer::~Renderer()
{
	Cleanup();
}

void Renderer::Initialize(const WindowSettings& windowSettings)
{
	// Why does this function throw errors, and not use the logger, you may ask?
	// As the ImGui logger can't be created if the window creation fails, having the errors logged in the logger would be useless

	// OpenGL versions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Window creation
	m_pWindow = SDL_CreateWindow(
		windowSettings.Name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		static_cast<int>(windowSettings.Width),
		static_cast<int>(windowSettings.Height),
		SDL_WINDOW_OPENGL);

	if (m_pWindow == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	// Create OpenGL context 
	m_pContext = SDL_GL_CreateContext(m_pWindow);
	if (m_pContext == nullptr)
	{
		throw std::runtime_error(std::string("SDL_GL_CreateContext Error: ") + SDL_GetError());
	}

	// Set the swap interval for the current OpenGL context,
	// synchronize it with the vertical retrace
	if (m_WindowSettings.EnableVSync)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			throw std::runtime_error(std::string("SDL_GL_SetSwapInterval Error: ") + SDL_GetError());
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, m_WindowSettings.Width, 0, m_WindowSettings.Height); // y from bottom to top
	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, static_cast<int>(m_WindowSettings.Width), static_cast<int>(m_WindowSettings.Height));

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glAlphaFunc(GL_GREATER, 0.5f);
	glEnable(GL_ALPHA_TEST);

	glEnable(GL_DEPTH_TEST);
	SDL_GL_MakeCurrent(m_pWindow, m_pContext);

	ImGui::CreateContext();
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
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(m_pContext);
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
}


void Renderer::RenderTexture(GLTextureWrapper* pTexture, const glm::vec2& pos, const glm::vec2& scale) const
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

			for (auto vertex : vertexBuffer)
			{
				glTexCoord2f(vertex.first.x, vertex.first.y);
				glVertex3f(vertex.second.x, vertex.second.y, 1.f - 1.f / static_cast<GLfloat>(pTexture->GetRenderPriority()));
			}

		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}


const std::array<VertexUV, 4> Renderer::CreateRenderParams(GLTextureWrapper* pTexture) const 
{
	const auto source = pTexture->GetSource();
	const auto textureWidth = pTexture->GetWidth();
	const auto textureHeight = pTexture->GetHeight();

	const auto targetWidth = (pTexture->GetTargetWidth() > 0.f) ? pTexture->GetTargetWidth() : ((source.Width > 0U) ? static_cast<float>(source.Width) : static_cast<float>(pTexture->GetWidth()));
	const auto targetHeight = (pTexture->GetTargetHeight() > 0.f) ? pTexture->GetTargetHeight() : ((source.Height > 0U) ? static_cast<float>(source.Height) : static_cast<float>(pTexture->GetHeight()));

	const auto targetPos = pTexture->GetPositionOffset();


	// Determine the texturecoordinates that should be rendered;
	float uvLeft{}, uvRight{}, uvTop{}, uvBottom{};

	if (!(source.Width > 0U && source.Height > 0U)) // No source specified
	{
		// Use complete texture
		uvLeft = 0.0f;
		uvRight = 1.0f;
		uvTop = 0.0f;
		uvBottom = 1.0f;
	}
	else // source specified
	{
		// Convert to the range [0.0, 1.0]
		uvLeft = static_cast<float>(source.Pos.x) / static_cast<float>(textureWidth);
		uvRight = static_cast<float>(source.Pos.x + static_cast<int32_t>(source.Width)) / static_cast<float>(textureWidth);
		uvTop = static_cast<float>(source.Pos.y) / static_cast<float>(textureHeight);
		uvBottom = static_cast<float>(source.Pos.y + static_cast<int32_t>(source.Height)) / static_cast<float>(textureHeight);
	}


	float vertexLeft{}, vertexBottom{}, vertexRight{}, vertexTop{};

	switch (pTexture->GetOffsetMode())
	{
	case TextureOffsetMode::CENTER:
		
		vertexLeft = targetPos.x - targetWidth / 2.f;
		vertexRight = targetPos.x + targetWidth / 2.f;
		vertexTop = targetPos.y + targetHeight / 2.f;
		vertexBottom = targetPos.y - targetHeight/ 2.f;
		break;
	case TextureOffsetMode::BASE:
		vertexLeft = targetPos.x - targetWidth / 2.f;
		vertexRight = targetPos.x + targetWidth / 2.f;
		vertexTop = targetPos.y + targetHeight;
		vertexBottom = targetPos.y;
		break;
	case TextureOffsetMode::TOP:
		vertexLeft = targetPos.x - targetWidth / 2.f;
		vertexRight = targetPos.x + targetWidth / 2.f;
		vertexTop = targetPos.y;
		vertexBottom = targetPos.y - targetHeight;
		break;
	case TextureOffsetMode::TOPLEFT:
		vertexLeft = targetPos.x;
		vertexRight = targetPos.x + targetWidth;
		vertexTop = targetPos.y;
		vertexBottom = targetPos.y - targetHeight;
		break;
	case TextureOffsetMode::BOTTOMLEFT:
		vertexLeft = targetPos.x;
		vertexRight = targetPos.x + targetWidth;
		vertexTop = targetPos.y + targetHeight;
		vertexBottom = targetPos.y;
		break;
	}

	return std::array<VertexUV, 4>
	{
		VertexUV(glm::vec2(uvLeft, uvBottom), glm::vec2(vertexLeft, vertexBottom)),
		VertexUV(glm::vec2(uvLeft, uvTop), glm::vec2(vertexLeft, vertexTop)),
		VertexUV(glm::vec2(uvRight, uvTop), glm::vec2(vertexRight, vertexTop)),
		VertexUV(glm::vec2(uvRight, uvBottom), glm::vec2(vertexRight, vertexBottom))
	};
}
