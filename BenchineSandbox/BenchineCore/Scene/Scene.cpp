#include "Scene.h"

#include <deque>
#include <future>
#include <string_view>

#include "Components/PhysicsComponent2D.h"
#include "Components/RenderComponent.h"
#include "Core/Memory.hpp"
#include "Debugging/Logger.hpp"
Scene::Scene(const std::string_view& sceneName)
	: m_Name(sceneName)
{
}

Scene::~Scene()
{
	for (auto pGameObject : m_pGameObjects)
	{
		SafeDelete(pGameObject);
	}
}

void Scene::BaseInitialize()
{
	// User Defined Initialize
	Initialize();

	// Game Object Initialization
	for (auto pGameObject : m_pGameObjects)
	{
		pGameObject->BaseInitialize();
	}
}

void Scene::BaseUpdate(const f32 dT)
{
	// User Defined Update
	Update(dT);

	// Game Object Update
	for (auto pGameObject = m_pGameObjects.begin(); pGameObject != m_pGameObjects.end();)
	{
		//https://stackoverflow.com/a/16269740
		(*pGameObject)->BaseUpdate(dT);
		if ((*pGameObject)->MarkedForDelete())
		{
			auto copy = pGameObject;
			pGameObject = ++pGameObject;
			RemoveGameObject(*copy);
		}
		else
		{
			++pGameObject;
		}
	}
	DoPhysics();
}

void Scene::Render() const
{
	for (const auto pRenderComponent : m_pRenderComponents)
	{
		if (pRenderComponent != nullptr)
		{
			pRenderComponent->Render();
			pRenderComponent->ClearBuffer();
		}
		else
		{
			LOG(Warning, "Trying to render deleted RenderComponent, remember to clean up render components when deleting an object that has one");
		}
	}
}

void Scene::DoPhysics()
{
	const u32 maxThreads = std::thread::hardware_concurrency();
	std::deque<std::future<void>> futures;
	u32 threadCounter = 0;

	for (const auto dynamicObject : m_pDynamicObjects)
	{
		if (threadCounter >= maxThreads)
		{
			futures.front().get();
			futures.pop_front();
			threadCounter--;
		}

		futures.emplace_back(std::async(std::launch::async, [=]()
		{
			for (const auto staticObject : m_pStaticObjects)
			{
				dynamicObject->HandleCollision(staticObject);
			}
		}));
		threadCounter++;

		if (threadCounter >= maxThreads)
		{
			futures.front().get();
			futures.pop_front();
			threadCounter--;
		}

		futures.emplace_back(std::async(std::launch::async, [=]()
		{
			for (const auto otherObject : m_pDynamicObjects)
			{
				if (dynamicObject != otherObject)
					dynamicObject->HandleCollision(otherObject);
			}
		}));
	}

	for (const auto trigger : m_pTriggers)
	{
		if (threadCounter >= maxThreads)
		{
			futures.front().get();
			futures.pop_front();
			threadCounter--;
		}

		futures.emplace_back(std::async(std::launch::async, [=]()
		{
			for (const auto dynamicObject : m_pDynamicObjects)
			{
				trigger->HandleCollision(dynamicObject);
			}
		}));
	}

	// Make sure that, at the end of this, every single collision calculation is done
	for (auto& future : futures)
	{
		future.get();
	}
}
GameObject* Scene::AddGameObject(GameObject* pGameObject) noexcept
{
	pGameObject->SetParentScene(this);
	m_pGameObjects.push_back(pGameObject);
	return pGameObject;
}

GameObject* Scene::AddGameObjectLate(GameObject* pGameObject) noexcept
{
	pGameObject->SetParentScene(this);
	pGameObject->BaseInitialize();
	m_pGameObjects.push_back(pGameObject);
	return pGameObject;
}

// For safety, return the deleted gameobject (now nullptr) to replace any reference in the caller
GameObject* Scene::RemoveGameObject(GameObject* pGameObject) noexcept
{
	if (pGameObject == nullptr)
	{
		LOG(Warning, "You just tried to remove a gameobject that was already nullptr");
		return pGameObject;
	}
	m_pGameObjects.remove(pGameObject);

	const auto pRenderComponent = pGameObject->GetRenderComponent();
	if (pRenderComponent != nullptr)
	{
		m_pRenderComponents.remove(pRenderComponent);
	}

	const auto pPhysicsComponents = pGameObject->GetComponents<PhysicsComponent2D>();
	if (!pPhysicsComponents.empty())
	{
		for (auto pPhysicsComponent : pPhysicsComponents)
		{
			switch (pPhysicsComponent->GetCollisionMode())
			{
			case CollisionMode::Dynamic:
				m_pDynamicObjects.remove(pPhysicsComponent);
				break;
			case CollisionMode::Static:
				m_pStaticObjects.remove(pPhysicsComponent);
				break;
			case CollisionMode::Trigger:
				m_pTriggers.remove(pPhysicsComponent);
				break;
			}
		}
	}
	SafeDelete(pGameObject);
	return pGameObject;
}

void Scene::AddRenderComponent(RenderComponent* pRenderComponent) noexcept
{
	m_pRenderComponents.push_back(pRenderComponent);
}

void Scene::RemoveRenderComponent(RenderComponent* pRenderComponent) noexcept
{
	m_pRenderComponents.remove(pRenderComponent);
}

void Scene::AddStaticObject(PhysicsComponent2D* pPhysicsComponent) noexcept
{
	m_pStaticObjects.push_back(pPhysicsComponent);
}

void Scene::AddDynamicObject(PhysicsComponent2D* pPhysicsComponent) noexcept
{
	m_pDynamicObjects.push_back(pPhysicsComponent);
}
void Scene::AddTrigger(PhysicsComponent2D* pPhysicsComponent) noexcept
{
	m_pTriggers.push_back(pPhysicsComponent);
}
