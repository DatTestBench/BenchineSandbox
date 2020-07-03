#pragma once
#include "Components/Components.h"
#include "Scene/Scene.h"
#include "Helpers/GeneralHelpers.h"
#include "Resources/Resources.h"
namespace Factories
{
	/*CHARACTER*/
	GameObject* CreateCharacter(const std::string& characterFile, const std::string& characterName, const glm::vec2& pos = glm::vec2(), const glm::vec2& scale = glm::vec2(1.f, 1.f));

	/*DROPS*/
	GameObject* CreateDrop(const std::string& dropFile, const std::string& dropName, const glm::vec2& pos = glm::vec2(), const glm::vec2& scale = glm::vec2(1.f, 1.f));


	GameObject* CreateBubble(const std::string& bubbleFile, const std::string& bubbleName, const glm::vec2& direction, const glm::vec2& pos = glm::vec2(), const glm::vec2& scale = glm::vec2(1.f, 1.f));	

	/*TESTOBJECT*/
	GameObject* CreateObject();

	/*Level*/
	GameObject* CreateLevel(const std::string& levelFile, const std::string& levelName);
}

/*auto pBackground = AddGameObject(new GameObject());
	pBackground->AddComponent(new RenderComponent());
	auto pTexture = pBackground->AddComponent(new TextureComponent(RESOURCES->Load<Texture2D>("Background.jpg")));
	pTexture->GetTexture()->SetOffsetMode(TextureOffsetMode::BOTTOMLEFT);
	const auto windowSettings = RENDERER->GetWindowSettings();
	pTexture->GetTexture()->SetTarget(windowSettings.Width, windowSettings.Height);*/