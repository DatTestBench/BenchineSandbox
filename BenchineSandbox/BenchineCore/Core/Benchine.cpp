#include "BenchinePCH.h"
#include "Core/Benchine.h"

#include "Core/Memory.hpp"
#include "Helpers/Singleton.hpp"
void Benchine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		throw std::runtime_error(std::string("Benchine::Initialize() > SDL_Init Error") + SDL_GetError());
	}
	RENDERER->Initialize(WindowSettings("Window", 1600U, 960U, false));
}

void Benchine::LoadGame() const
{
	m_pGame->BaseInitialize();
}

void Benchine::Cleanup()
{
	SafeDelete(m_pGame);
	
	// Cleanup singletons
	SceneManager::Destroy();
	ResourceManager::Destroy();
	InputManager::Destroy();
	Logger::Destroy();
	Renderer::Destroy();

	// SDL
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
