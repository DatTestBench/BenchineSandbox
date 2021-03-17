#include "SandboxPCH.h"
#include "Sandbox.h"
#include "Scenes/TestScene.h"
#include "Scenes/NodeEditorScene.h"


// This is the only actual useful function here >_>
void Sandbox::Initialize()
{
	SceneManager::GetInstance()->AddScene(new TestScene("TestScene"));
	SceneManager::GetInstance()->AddScene(new NodeEditorScene("NodeEditorScene"));
	SceneManager::GetInstance()->SetStartScene("NodeEditorScene");

	SceneManager::GetInstance()->Initialize();

	LOG(LEVEL_INFO, "{0} Test", "Info");
	LOG(LEVEL_WARNING, "{0} Test", "Warning");
	LOG(LEVEL_ERROR, "{0} Test", "Error");
	LOG(LEVEL_DEBUG, "{0} Test", "Debug");
	LOG(LEVEL_SUCCESS, "{0} Test", "Success");
}

void Sandbox::Update([[maybe_unused]] const f32 dT)
{
}



