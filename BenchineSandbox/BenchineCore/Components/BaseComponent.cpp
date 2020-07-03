#include "BenchinePCH.h"
#include "Components/BaseComponent.h"
#include "Scene/GameObject.h"
#include "Components/TransformComponent.h"
BaseComponent::BaseComponent()
	: m_pGameObject(nullptr)
	, m_IsInitialized(false)
{

}

void BaseComponent::BaseInitialize()
{
	if (m_IsInitialized)
		return;

	Initialize();

	m_IsInitialized = true;
}