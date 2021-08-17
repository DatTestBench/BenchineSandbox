#pragma once
#include "Scene/Scene.h"
#include "Components/Components.h"
#include "NodeEditor/BNEditor.h"

class TestScene final : public Scene
{
public:
	explicit TestScene(const std::string_view& sceneName);

protected:
	void Initialize() override;
	void Update([[maybe_unused]] f32 dT) override;

private:
	GameObject* m_pFPSCounter;
	FPSComponent* m_pFPSComponent;
	TextComponent* m_pFPSText;

	BNEditor m_Editor;
};
