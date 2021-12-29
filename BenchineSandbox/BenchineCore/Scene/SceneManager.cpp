#include "Scene/SceneManager.h"
#include <ranges>
#include "Scene/DefaultScene.h"
#include "Core/Memory.hpp"
#include "Debugging/Logger.hpp"
SceneManager::SceneManager(Token)
	: m_pCurrentScene(nullptr)
	, m_pSceneToLoad(nullptr)
	, m_IsInitialized(false)
{
}

SceneManager::~SceneManager()
{
	for (auto pScene : m_pScenes | std::views::values)
	{
		SafeDelete(pScene);
	}
}

void SceneManager::Initialize()
{
	if (m_IsInitialized)
		return;

	if (m_pScenes.empty())
	{
		LOG(Warning, "No scenes loaded, falling back on default scene");

		auto pDefaultScene = new DefaultScene;

		m_pScenes.try_emplace("DefaultScene", pDefaultScene);

		m_pCurrentScene = pDefaultScene;
	}

	for (const auto pScene : m_pScenes | std::views::values)
	{
		pScene->BaseInitialize();
	}

	m_IsInitialized = true;
}

void SceneManager::Update(const f32 dT)
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

	LOG_CONDITIONAL(currentSize == m_pScenes.size(), Warning, "A Scene with name: {0} already exists, the scene was not added", pScene->GetSceneName());
}

void SceneManager::LoadScene(const std::string_view& sceneName)
{
	if (const auto pSceneToLoad = m_pScenes.find(sceneName); pSceneToLoad != m_pScenes.cend())
	{
		m_pSceneToLoad = pSceneToLoad->second;
		return;
	}

	LOG(Error, "Scene: {0} not found, loading failed", sceneName);
}

void SceneManager::SetStartScene(const std::string_view& sceneName)
{
	if (const auto pStartScene = m_pScenes.find(sceneName); pStartScene != m_pScenes.cend())
	{
		m_pCurrentScene = pStartScene->second;
		return;
	}

	LOG(Warning, "Scene: {0} not found, defaulting to first scene in the map if present", sceneName);

	if (m_pScenes.empty())
	{
		LOG(Error, "No scenes present");
		return;
	}

	m_pCurrentScene = m_pScenes.begin()->second;
}

void SceneManager::RenderCurrentScene() const
{
	m_pCurrentScene->Render();
}
