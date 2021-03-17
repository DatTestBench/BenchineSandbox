#include "BenchinePCH.h"
#include "Scene/GameObject.h"
#include "Components/BaseComponent.h"
#include "Components/TransformComponent.h"
#include "Resources/ResourceManager.h"

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
	for (auto pComponent : m_pComponents)
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
	for (auto pComponent : m_pComponents)
	{
		pComponent->Update(dT);
	}
}

void GameObject::SetParentScene(Scene* pScene)
{
	if (m_pParentScene != nullptr)
	{
		LOG(LEVEL_WARNING, "Object is already parented to another scene, is this reparenting intentional?");
	}
	if (m_pParentObject != nullptr)
	{
		LOG(LEVEL_WARNING, "Object is already parented to an object, is this reparenting intentional?");
		m_pParentObject = nullptr;
	}
	m_pParentScene = pScene;
}

void GameObject::SetParentObject(GameObject* pObject)
{
	if (m_pParentObject != nullptr)
	{
		LOG(LEVEL_WARNING, "Object is already parented to another object, is this reparenting intentional?");
	}
	if (m_pParentScene != nullptr)
	{
		LOG(LEVEL_WARNING, "Object is already parented to a scene, is this reparenting intentional?");
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

	LOG(LEVEL_ERROR, "Object has no parent scene or gameobject");
	return nullptr;
}
