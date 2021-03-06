#pragma once
#include "Scene/Scene.h"
class DefaultScene final : public Scene
{
public:
	explicit DefaultScene(const std::string_view& sceneName = "DefaultScene");
	~DefaultScene() override = default;
	DEL_ROF(DefaultScene)
protected:
	void Initialize() override;
	void Update(f32 dT) override;
};
