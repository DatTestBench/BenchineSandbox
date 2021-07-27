#pragma once
#include "Scene/Scene.h"
#include "NodeEditor/BNEditor.h"
class NodeEditorScene final : public Scene
{
public:
	explicit NodeEditorScene(const std::string_view& sceneName);

protected:
	void Initialize() override;
	void Update([[maybe_unused]] f32 dT) override;

private:
	BNEditor m_Editor;
};