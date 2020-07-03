#include "SandboxPCH.h"
#include "Sandbox.h"
#include "Scenes/TestScene.h"


// This is the only actual useful function here >_>
void Sandbox::Initialize()
{
	SceneManager::GetInstance()->AddScene(new TestScene("TestScene"));

	SceneManager::GetInstance()->SetStartScene("TestScene");

	SceneManager::GetInstance()->Initialize();
	
}

void Sandbox::Update([[maybe_unused]] float dT)
{
}



