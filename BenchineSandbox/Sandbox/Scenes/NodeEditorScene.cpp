#include "SandboxPCH.h"
#include "Scenes/NodeEditorScene.h"
#include "NodeEditor/BNNodes.h"
NodeEditorScene::NodeEditorScene(const std::string_view& sceneName)
	: Scene(sceneName)
	, editor("TestEditor")
{
}

NodeEditorScene::~NodeEditorScene()
{
}

void NodeEditorScene::Initialize()
{
	editor.Initialize();
}

void NodeEditorScene::Update([[maybe_unused]] float dT)
{
	editor.Update(dT);
}
