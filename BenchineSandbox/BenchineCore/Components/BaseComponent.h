#pragma once
#include "Core/CoreBasicTypes.hpp"

#include "Scene/GameObject.h"

class TransformComponent;
class BaseComponent
{
public:
	virtual ~BaseComponent() = default;

	[[nodiscard]] constexpr auto GetGameObject() const noexcept -> GameObject* { return m_pRootObject; }
	[[nodiscard]] constexpr auto GetTransform() const noexcept -> TransformComponent* { return m_pRootObject->GetTransform(); }

	void BaseInitialize();
	virtual void Update(f32 dT) = 0;

protected:
	friend GameObject;
	virtual void Initialize() = 0;

	GameObject* m_pRootObject = nullptr;
	bool m_IsInitialized = false;
};
