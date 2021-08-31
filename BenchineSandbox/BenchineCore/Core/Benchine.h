#pragma once
#include <chrono>
#include <memory>

#include "BaseGame.h"
#include "CoreBasicTypes.hpp"
#include "InputManager.h"
#include "Debugging/Logger.hpp"
#include "Graphics/Renderer.h"
#include "Helpers/Concepts.hpp"
#include "Resources/ResourceManager.h"
#include "Scene/SceneManager.h"

struct SDL_Window;
class Benchine
{
public:
	template<IsGame GameInstance> // Templated to allow the use of any kind of basegame
	void Run(const std::string_view name)
	{
		m_pGame = std::make_unique<GameInstance>(name);
		//m_pGame = new GameInstance();
		Initialize(); // Setup SDL

		RESOURCES->Initialize("../Resources/");

		LoadGame();

		bool quit = false;

		auto lastTime = std::chrono::high_resolution_clock::now();

		const auto pLogger = LOGGER;

		// TODO(long term): fix timestep
		while (!quit)
		{
			
			auto currentTime = std::chrono::high_resolution_clock::now();
			const f32 deltaTime = std::min(std::chrono::duration<f32>(currentTime - lastTime).count(), 0.1f);
			lastTime = currentTime;
			quit = INPUT->ProcessInput();
			
			RENDERER->SetupRender();
			SCENES->RenderCurrentScene();
			pLogger->OutputLog();
			m_pGame->BaseUpdate(deltaTime);
			RENDERER->PresentRender();
		}
		Cleanup();

	}

private:	
	static void Initialize();
	void LoadGame() const;
	static void Cleanup();

	static constexpr i32 MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps

	// TODO: potentially unique_ptr
	std::unique_ptr<BaseGame> m_pGame = nullptr;
};