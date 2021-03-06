#pragma once
#include "Scene/Scene.h"
#include "Components/Components.h"

class TestScene final : public Scene
{
public:
	explicit TestScene(const std::string_view& sceneName);
	virtual ~TestScene() override;
	DEL_ROF(TestScene)

protected:
	void Initialize() override;
	void Update([[maybe_unused]] f32 dT) override;

private:
	GameObject* m_pFPSCounter;
	FPSComponent* m_pFPSComponent;
	TextComponent* m_pFPSText;
};