#pragma once
#include "Helpers/Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	
	SceneManager(token);
	virtual ~SceneManager();
	void Initialize();
	void Update(float dT);

	void AddScene(Scene* pScene);
	void LoadScene(const std::string_view& sceneName);
	
	void SetStartScene(const std::string_view& sceneName);
	void RenderCurrentScene();



private:
	std::map<std::string_view, Scene*> m_pScenes;
	Scene* m_pCurrentScene;
	Scene* m_pSceneToLoad;
	
	bool m_IsInitialized;
};

