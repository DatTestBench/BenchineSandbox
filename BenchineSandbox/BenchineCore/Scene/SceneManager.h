#pragma once
#include "Helpers/Singleton.hpp"
#include <map>
#include <string_view>

#include "Core/CoreBasicTypes.hpp"
class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	explicit SceneManager(Token);
	~SceneManager();
	void Initialize();
	void Update(f32 dT);

	void AddScene(Scene* pScene);
	void LoadScene(const std::string_view& sceneName);

	void SetStartScene(const std::string_view& sceneName);
	void RenderCurrentScene() const;

private:
	std::map<std::string_view, Scene*> m_pScenes;
	Scene* m_pCurrentScene;
	Scene* m_pSceneToLoad;

	bool m_IsInitialized;
};

#define SCENES SceneManager::GetInstance()
