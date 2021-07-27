#pragma once
#include "Scene/GameObject.h"

class TransformComponent;
class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent() = default;
	DEL_ROF(BaseComponent)

	[[nodiscard]] constexpr auto GetGameObject() const noexcept -> GameObject* { return m_pGameObject; }
	[[nodiscard]] constexpr auto GetTransform() const noexcept -> TransformComponent* { return m_pGameObject->GetTransform(); }

	void BaseInitialize();
	virtual void Update(f32 dT)  = 0;

protected:
	friend GameObject;
	virtual void Initialize() = 0;

	GameObject* m_pGameObject; // object this is attached to
	bool m_IsInitialized;
};
