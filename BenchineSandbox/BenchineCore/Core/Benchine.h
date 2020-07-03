#pragma once
struct SDL_Window;
#include "Core/BaseGame.h"


class Benchine
{
public:
	

	template<typename T> // Templated to allow the use of any kind of basegame
	void Run()
	{
		m_pGame = new T();

		Initialize(); // Setup SDL

		RESOURCES->Initialize("../Resources/");
		DEBUGONLY(Logger* pLogger = Logger::GetInstance());

		LoadGame();

		bool quit = false;

		auto lastTime = std::chrono::high_resolution_clock::now();
		//float lag = 0.f;

		while (!quit)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::min(std::chrono::duration<float>(currentTime - lastTime).count(), 0.1f);
			lastTime = currentTime;
			//lag += deltaTime;
			quit = INPUT->ProcessInput();

			
			RENDERER->SetupRender();
			SceneManager::GetInstance()->RenderCurrentScene();
			DEBUGONLY(pLogger->OutputLog());
			m_pGame->BaseUpdate(deltaTime);
			RENDERER->PresentRender();
			//std::this_thread::sleep_until(currentTime + std::chrono::milliseconds(MsPerFrame));
			/*RENDERER->SetupRender();
			SceneManager::GetInstance()->RenderCurrentScene();
			while (lag >= MsPerFrame / 1000.f)
			{
				DEBUGONLY(pLogger->OutputLog());
				m_pGame->BaseUpdate(MsPerFrame / 1000.f);
				lag -= MsPerFrame / 1000.f;
			}
			RENDERER->PresentRender();*/
		
		}
		Cleanup();

		
	}

private:
	void Initialize();
	void LoadGame() const;
	void Cleanup();

	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps

	BaseGame* m_pGame;
};