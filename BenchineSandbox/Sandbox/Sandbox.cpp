#include "SandboxPCH.h"
#include "Sandbox.h"
#include "Scenes/TestScene.h"
#include "Scenes/NodeEditorScene.h"

void Sandbox::Initialize()
{
	SceneManager::GetInstance()->AddScene(new TestScene("TestScene"));
	SceneManager::GetInstance()->AddScene(new NodeEditorScene("NodeEditorScene"));
	SceneManager::GetInstance()->SetStartScene("TestScene");

	SceneManager::GetInstance()->Initialize();

	LOG(Info, "{0} Test", "Info");
	LOG(Warning, "{0} Test", "Warning");
	LOG(Error, "{0} Test", "Error");
	LOG(Debug, "{0} Test", "Debug");
	LOG(Success, "{0} Test", "Success");
}

void Sandbox::Update(const f32)
{
}



