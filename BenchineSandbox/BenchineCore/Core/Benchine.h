#pragma once
struct SDL_Window;
#include "Core/BaseGame.h"
#include "Helpers/Concepts.hpp"

class Benchine
{
public:
	template<IsGame GameInstance> // Templated to allow the use of any kind of basegame
	void Run()
	{
		//m_pGame = std::make_unique<GameInstance>();
		m_pGame = new GameInstance();
		Initialize(); // Setup SDL

		RESOURCES->Initialize("../Resources/");

		LoadGame();

		bool quit = false;

		auto lastTime = std::chrono::high_resolution_clock::now();
		
		auto pLogger = Logger::GetInstance();

		// todo(long term): fix timestep
		while (!quit)
		{
			
			auto currentTime = std::chrono::high_resolution_clock::now();
			const f32 deltaTime = std::min(std::chrono::duration<f32>(currentTime - lastTime).count(), 0.1f);
			lastTime = currentTime;
			quit = INPUT->ProcessInput();
			
			RENDERER->SetupRender();
			SceneManager::GetInstance()->RenderCurrentScene();
			pLogger->OutputLog();
			m_pGame->BaseUpdate(deltaTime);
			RENDERER->PresentRender();
		}
		Cleanup();

	}

private:	
	static void Initialize();
	void LoadGame() const;
	void Cleanup();

	static const i32 MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps

	// TODO: potentially unique_ptr
	BaseGame* m_pGame = nullptr;
};