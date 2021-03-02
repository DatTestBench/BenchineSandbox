#pragma once

#include "Helpers/Utils.hpp"
#include "Scene/Scene.h"

#include "Helpers/Concepts.hpp"

class TransformComponent;
class RenderComponent;
class BaseComponent;
class GameObject final
{
public:
	GameObject();
	virtual ~GameObject();
	DEL_ROF(GameObject)

	void BaseInitialize();
	void BaseUpdate(float dT);

	/**
	 * Adds a component to the current gameobject
	 * @param pComponent The component that will be added to the scene
	 * @return The component passed, returned for further use
	 * */
	template <IsComponent Component>
	Component* AddComponent(Component* pComponent)
	{
		m_pComponents.push_back(pComponent);
		pComponent->m_pGameObject = this;
		return pComponent;
	}

	void SetParentScene(Scene* pScene);
	void SetParentObject(GameObject* pObject);
	void SetRenderComponent(RenderComponent* pRenderComponent) { m_pRenderComponent = pRenderComponent; }
	[[nodiscard]] constexpr auto GetTransform() const noexcept -> TransformComponent* { return m_pTransform; }
	[[nodiscard]] constexpr auto GetRenderComponent() const noexcept -> RenderComponent* { return m_pRenderComponent; }
	[[nodiscard]] constexpr auto MarkedForDelete() const noexcept -> bool { return m_MarkedForDelete; }
	[[nodiscard]] auto GetScene() const noexcept -> Scene*;
	void MarkForDelete() { m_MarkedForDelete = true; }

	template <IsComponent Component>
	Component* GetComponent()
	{
		const type_info& ti = typeid(Component);
		for (auto* component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
				return static_cast<Component*>(component);
		}
		return nullptr;
	}

	template <IsComponent Component>
	std::vector<Component*> GetComponents()
	{
		const type_info& ti = typeid(Component);
		std::vector<Component*> pComponents;
		for (auto* pComponent : m_pComponents)
		{
			if (pComponent && typeid(*pComponent) == ti)
			{
				pComponents.push_back(static_cast<Component*>(pComponent));
			}
		}
		return pComponents;
	}

protected:
	// For future use
	virtual void Initialize()
	{
	}
	virtual void Update([[maybe_unused]] float dT)
	{
	}

private:
	Scene* m_pParentScene;
	GameObject* m_pParentObject;
	std::list<BaseComponent*> m_pComponents;
	bool m_IsInitialized;
	TransformComponent* m_pTransform;
	RenderComponent* m_pRenderComponent;
	bool m_MarkedForDelete;
};
