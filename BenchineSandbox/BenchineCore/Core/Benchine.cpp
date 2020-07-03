#include "BenchinePCH.h"
#include "Core/Benchine.h"
#include "Helpers/Singleton.h"
void Benchine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		throw std::runtime_error(std::string("Benchine::Initialize() > SDL_Init Error") + SDL_GetError());
	}
	RENDERER->Initialize(WindowSettings("Window", 1600U, 960U, true));

}

void Benchine::LoadGame() const
{
	m_pGame->BaseInitialize();
}

void Benchine::Cleanup()
{

	delete m_pGame;
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
