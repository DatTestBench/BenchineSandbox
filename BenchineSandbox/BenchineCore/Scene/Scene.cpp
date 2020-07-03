#include "BenchinePCH.h"
#include "Scene/Scene.h"
#include "Scene/GameObject.h"
#include "Components/RenderComponent.h"
#include "Helpers/SAT.h"
#include "Components/PhysicsComponent2D.h"
#include "Debugging/DebugRenderer.h"
#include <future>
#include <deque>
Scene::Scene(const std::string_view& name)
	: m_Name(name)
	, m_pGameObjects()
	, m_pRenderComponents()
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

void Scene::BaseUpdate(float dT)
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

	for (auto pRenderComponent : m_pRenderComponents)
	{
		if (pRenderComponent != nullptr)
		{
			pRenderComponent->Render();
			pRenderComponent->ClearBuffer();
		}
		else
		{
			DEBUGONLY(Logger::Log<LEVEL_WARNING>("Scene::Render") << "Trying to render deleted RenderComponent, remember to clean up render components when deleting an object that has one");
		}
	}
}

void Scene::DoPhysics()
{
	uint32_t maxThreads = std::thread::hardware_concurrency();
	std::deque<std::future<void>> futures;
	uint32_t threadCounter = 0;	

	for (auto dynamicObject : m_pDynamicObjects)
	{
		if (threadCounter >= maxThreads)
		{
			futures.front().get();
			futures.pop_front();
			threadCounter--;
		}

		futures.emplace_back(std::async(std::launch::async, [=](){
			for (auto staticObject : m_pStaticObjects)
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

		futures.emplace_back(std::async(std::launch::async, [=](){
			for (auto otherObject : m_pDynamicObjects)
			{
				if (dynamicObject != otherObject)
					dynamicObject->HandleCollision(otherObject);
			}
		}));
	}

	for (auto trigger : m_pTriggers)
	{
		if (threadCounter >= maxThreads)
		{
			futures.front().get();
			futures.pop_front();
			threadCounter--;
		}

		futures.emplace_back(std::async(std::launch::async, [=](){
			for (auto dynamicObject : m_pDynamicObjects)
			{
				trigger->HandleCollision(dynamicObject);
			}
		}));
	}

	// Make sure that, at the end of this, every single collsion calculation is done
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
		DEBUGONLY(Logger::Log<LEVEL_WARNING>("Scene::RemoveGameObject") << "You just tried to remove a gameobject that was already nullptr");
		return pGameObject;
	}
	m_pGameObjects.remove(pGameObject);

	auto pRenderComponent = pGameObject->GetRenderComponent();
	if (pRenderComponent != nullptr)
	{
		m_pRenderComponents.remove(pRenderComponent);
	}

	auto pPhysicsComponents = pGameObject->GetComponents<PhysicsComponent2D>();
	if (!pPhysicsComponents.empty())
	{
		for (auto pPhysicsComponent : pPhysicsComponents)
		{
			switch (pPhysicsComponent->GetCollisionMode())
			{
			case CollisionMode::DYNAMIC:
				m_pDynamicObjects.remove(pPhysicsComponent);
				break;
			case CollisionMode::STATIC:
				m_pStaticObjects.remove(pPhysicsComponent);
				break;
			case CollisionMode::TRIGGER:
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