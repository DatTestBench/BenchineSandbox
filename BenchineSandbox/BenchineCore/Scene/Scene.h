#pragma once

class GameObject;
class RenderComponent;
class PhysicsComponent2D;
class Scene
{
public:

	explicit Scene(const std::string_view& sceneName);
	virtual ~Scene();
	DEL_ROF(Scene)

	void BaseInitialize();
	void BaseUpdate(f32 dT);
	void Render() const;
	void DoPhysics();

	GameObject* AddGameObject(GameObject* pGameObject) noexcept;
	GameObject* AddGameObjectLate(GameObject* pGameObject) noexcept;
	GameObject* RemoveGameObject(GameObject* pGameObject) noexcept;

	void AddRenderComponent(RenderComponent* pRenderComponent) noexcept;
	void RemoveRenderComponent(RenderComponent* pRenderComponent) noexcept;

	void AddStaticObject(PhysicsComponent2D* pPhysicsComponent) noexcept;
	void AddDynamicObject(PhysicsComponent2D* pPhysicsComponent) noexcept;
	void AddTrigger(PhysicsComponent2D* pPhysicsComponent) noexcept;

	[[nodiscard]] constexpr auto GetSceneName() const noexcept -> std::string_view { return m_Name; }

protected:
	virtual void Initialize() = 0;
	virtual void Update(f32 dT) = 0;

private:
	std::string_view m_Name;
	std::list<GameObject*> m_pGameObjects;
	std::list<RenderComponent*> m_pRenderComponents; // Caching the render components to prevent having to do GetComponent every frame;

	std::list<PhysicsComponent2D*> m_pDynamicObjects;
	std::list<PhysicsComponent2D*> m_pStaticObjects;
	std::list<PhysicsComponent2D*> m_pTriggers;
};
