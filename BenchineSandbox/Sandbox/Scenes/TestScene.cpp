#include "SandboxPCH.h"
#include "Scenes/TestScene.h"
#include "Debugging/DebugRenderer.h"
#include "Factories/Factories.h"
TestScene::TestScene(const std::string_view& sceneName)
	: Scene(sceneName)
	, m_pFPSComponent(nullptr)
	, m_pFPSCounter(nullptr)
	, m_pFPSText(nullptr)
{

}

TestScene::~TestScene()
{

}

void TestScene::Initialize()
{
	auto font = RESOURCES->Load<Font>("Lingua.otf");

	
	// FPS
	m_pFPSCounter = AddGameObject(new GameObject());
	m_pFPSCounter->GetTransform()->SetPosition(0.f, static_cast<float>(RENDERER->GetWindowSettings().Height));
	m_pFPSCounter->AddComponent(new RenderComponent());
	m_pFPSComponent = m_pFPSCounter->AddComponent(new FPSComponent());
	m_pFPSText = m_pFPSCounter->AddComponent(new TextComponent("a", font));
	m_pFPSText->SetColor(0, 255, 0);
	m_pFPSText->GetTexture()->SetOffsetMode(TextureOffsetMode::TOPLEFT);
	m_pFPSText->GetTexture()->SetRenderPriority(10U);
}

void TestScene::Update([[maybe_unused]] float dT)
{
	m_pFPSText->SetText(std::to_string(m_pFPSComponent->GetFPS()));
}