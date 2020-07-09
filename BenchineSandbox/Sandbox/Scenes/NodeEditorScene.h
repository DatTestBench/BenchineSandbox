#pragma once
#include "Scene/Scene.h"
#include "NodeEditor/BNEditor.h"
class NodeEditorScene final : public Scene
{
public:
	NodeEditorScene(const std::string_view& sceneName);
	virtual ~NodeEditorScene();
	DEL_ROF(NodeEditorScene)

protected:
	void Initialize() override;
	void Update([[maybe_unused]] float dT) override;

private:
	BNEditor editor;
};