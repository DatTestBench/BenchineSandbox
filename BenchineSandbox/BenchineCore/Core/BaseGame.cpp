#include "BenchinePCH.h"
#include "Core/BaseGame.h"

void BaseGame::BaseInitialize()
{
	// User Defined Initialize
	Initialize();
}

void BaseGame::BaseUpdate(const f32 dT)
{
	SceneManager::GetInstance()->Update(dT);
	// User Defined Update
	Update(dT);
}