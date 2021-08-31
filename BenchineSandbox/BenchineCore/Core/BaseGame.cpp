#include "Core/BaseGame.h"

#include "Scene/SceneManager.h"

void BaseGame::BaseInitialize()
{
	// User Defined Initialize
	Initialize();
}

void BaseGame::BaseUpdate(const f32 dT)
{
	SCENES->Update(dT);
	// User Defined Update
	Update(dT);
}