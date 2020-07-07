#pragma once
#include "Scene/Scene.h"

class NodeEditorScene final : public NodeEditorScene
{
public:
	NodeEditorScene(const std::string_view& sceneName);
	virtual ~NodeEditorScene() override;
	DEL_ROF(NodeEditorScene)

protected:
	void Initialize() override;
	void Update([[maybe_unused]] float dT) override;

private:

};