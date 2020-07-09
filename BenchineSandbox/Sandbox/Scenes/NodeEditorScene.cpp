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
	auto node = editor.AddNode(Nodes::SpawnInt());
	NodeEd::SetNodePosition(node->nodeId, ImVec2(0,0));
	node = editor.AddNode(Nodes::SpawnInt());
	NodeEd::SetNodePosition(node->nodeId, ImVec2(0, 0));
	node = editor.AddNode(Nodes::SpawnAddition());
	NodeEd::SetNodePosition(node->nodeId, ImVec2(50, 0));
	node = editor.AddNode(Nodes::SpawnIntToString());
	NodeEd::SetNodePosition(node->nodeId, ImVec2(100, 0));
	node = editor.AddNode(Nodes::SpawnPrintNode());
	NodeEd::SetNodePosition(node->nodeId, ImVec2(150, 0));

	NodeEd::NavigateToContent();
}

void NodeEditorScene::Update([[maybe_unused]] float dT)
{
	editor.Update(dT);
}