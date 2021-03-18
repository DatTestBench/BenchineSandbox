#pragma once
#include "Helpers/Singleton.hpp"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	explicit SceneManager(Token);
	virtual ~SceneManager();
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
