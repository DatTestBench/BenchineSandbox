#include "Components/BaseComponent.h"

void BaseComponent::BaseInitialize()
{
	if (m_IsInitialized)
		return;

	Initialize();

	m_IsInitialized = true;
}
