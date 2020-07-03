#include "BenchinePCH.h"
#include "Core/BaseGame.h"

void BaseGame::BaseInitialize()
{
	// User Definined Initialize
	Initialize();
}

void BaseGame::BaseUpdate(float dT)
{
	SceneManager::GetInstance()->Update(dT);
	// User Defined Update
	Update(dT);
}