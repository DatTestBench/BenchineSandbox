#include "SandboxPCH.h"
#include "Scenes/NodeEditorScene.h"
#include "NodeEditor/BNNodes.h"
NodeEditorScene::NodeEditorScene(const std::string_view& sceneName)
	: Scene(sceneName)
	, m_Editor("TestEditor")
{
}

void NodeEditorScene::Initialize()
{
	m_Editor.Initialize();
}

void NodeEditorScene::Update(const f32 dT)
{
	m_Editor.Update(dT);
}
