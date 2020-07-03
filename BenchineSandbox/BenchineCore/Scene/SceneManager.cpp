#include "BenchinePCH.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/DefaultScene.h"

SceneManager::SceneManager(token)
	: m_pScenes()
	, m_pCurrentScene(nullptr)
	, m_pSceneToLoad(nullptr)
	, m_IsInitialized(false)
{

}

SceneManager::~SceneManager()
{
	for (auto pScene : m_pScenes)
	{
		SafeDelete(pScene.second);
	}
}

void SceneManager::Initialize()
{
	if (m_IsInitialized)
		return;

	if (m_pScenes.empty())
	{
		DEBUGONLY(Logger::Log<LEVEL_WARNING>("SceneManager::SetStartScene") << "No scenes loaded, falling back on default scene");

		auto pDefaultScene = new DefaultScene;

		m_pScenes.try_emplace("DefaultScene", pDefaultScene);

		m_pCurrentScene = pDefaultScene;
	}

	for (auto pScene : m_pScenes)
	{
		pScene.second->BaseInitialize();
	}

	m_IsInitialized = true;
}

void SceneManager::Update(float dT)
{
	if (m_pSceneToLoad != nullptr)
	{
		m_pCurrentScene = m_pSceneToLoad;
		m_pSceneToLoad = nullptr;
	}

	m_pCurrentScene->BaseUpdate(dT);
}

void SceneManager::AddScene(Scene* pScene)
{
	const auto currentSize = m_pScenes.size();
	m_pScenes.try_emplace(pScene->GetSceneName(), pScene);

	if (currentSize == m_pScenes.size())
	{
		DEBUGONLY(Logger::Log<LEVEL_WARNING>("SceneManager::AddScene()") << "A Scene with name: " << pScene->GetSceneName() << " already exists, the scene was not added.");
	}
}

void SceneManager::LoadScene(const std::string_view& sceneName)
{
	auto pSceneToLoad = m_pScenes.find(sceneName);

	if (pSceneToLoad != m_pScenes.cend())
	{
		m_pSceneToLoad = (*pSceneToLoad).second;
		return;
	}

	DEBUGONLY(Logger::Log<LEVEL_ERROR>("SceneManager::LoadScene") << "Scene: " << sceneName << " not found, loading failed");
}

void SceneManager::SetStartScene(const std::string_view& sceneName)
{
	auto pStartScene = m_pScenes.find(sceneName);

	if (pStartScene != m_pScenes.cend())
	{
		m_pCurrentScene = (*pStartScene).second;
		return;
	}

	DEBUGONLY(Logger::Log<LEVEL_WARNING>("SceneManager::SetStartScene") << "Scene: " << sceneName << " not found, defaulting to first scene in the map if present");

	if (m_pScenes.empty())
	{
		return;
	}
	m_pCurrentScene = (*m_pScenes.begin()).second;

}

void SceneManager::RenderCurrentScene()
{
	m_pCurrentScene->Render();
}