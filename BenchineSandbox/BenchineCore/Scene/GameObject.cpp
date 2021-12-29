#include "Scene/GameObject.h"

#include "Core/Memory.hpp"
#include "Debugging/Logger.hpp"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
GameObject::GameObject()
	: m_IsInitialized(false)
	, m_pTransform(nullptr)
	, m_MarkedForDelete(false)
{
	m_pTransform = new TransformComponent();
	AddComponent(m_pTransform);
}

GameObject::~GameObject()
{
	for (auto pComponent : m_pComponents)
	{
		SafeDelete(pComponent);
	}
}

void GameObject::BaseInitialize()
{
	if (m_IsInitialized)
		return;

	// User Defined Initialization
	Initialize();

	// Component Initialization
	for (const auto pComponent : m_pComponents)
	{
		pComponent->BaseInitialize();
	}

	m_IsInitialized = true;
}
void GameObject::BaseUpdate(const f32 dT)
{
	// User Defined Update
	Update(dT);

	// Component Update
	for (const auto pComponent : m_pComponents)
	{
		pComponent->Update(dT);
	}
}

void GameObject::SetParentScene(Scene* pScene) noexcept
{
	LOG_CONDITIONAL(m_pParentScene != nullptr, Warning, "Object is already parented to another scene, is this reparenting intentional?");

	if (m_pParentObject != nullptr)
	{
		LOG(Warning, "Object is already parented to an object, is this reparenting intentional?");
		m_pParentObject = nullptr;
	}
	m_pParentScene = pScene;
}

void GameObject::SetParentObject(GameObject* pObject) noexcept
{
	LOG_CONDITIONAL(m_pParentObject != nullptr, Warning, "Object is already parented to another object, is this reparenting intentional?");

	if (m_pParentScene != nullptr)
	{
		LOG(Warning, "Object is already parented to a scene, is this reparenting intentional?");
		m_pParentScene = nullptr;
	}
	m_pParentObject = pObject;
}

Scene* GameObject::GetScene() const noexcept
{
	if (m_pParentObject != nullptr)
	{
		return m_pParentObject->GetScene();
	}

	if (m_pParentScene != nullptr)
	{
		return m_pParentScene;
	}

	LOG(Warning, "Object has no parent scene or gameobject");
	return nullptr;
}
