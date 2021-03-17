#include "SandboxPCH.h"
#include "Scenes/TestScene.h"
#include "Factories/Factories.h"

struct LinkInfo
{
};

TestScene::TestScene(const std::string_view& sceneName)
	: Scene(sceneName)
	, m_pFPSCounter(nullptr)
	, m_pFPSComponent(nullptr)
	, m_pFPSText(nullptr)
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	const auto font = RESOURCES->Load<Font>("Lingua.otf");

	m_pFPSCounter = AddGameObject(new GameObject());
	m_pFPSCounter->GetTransform()->SetPosition(0.f, static_cast<f32>(RENDERER->GetWindowSettings().Height));
	m_pFPSCounter->AddComponent(new RenderComponent());
	m_pFPSComponent = m_pFPSCounter->AddComponent(new FPSComponent());
	m_pFPSText = m_pFPSCounter->AddComponent(new TextComponent("a", font));
	m_pFPSText->SetColor(0, 255, 0);
	m_pFPSText->GetTexture()->SetOffsetMode(TextureOffsetMode::TOPLEFT);
	m_pFPSText->GetTexture()->SetRenderPriority(10U);
}

void ImGuiEx_BeginColumn()
{
	ImGui::BeginGroup();
}

void ImGuiEx_NextColumn()
{
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
}

void ImGuiEx_EndColumn()
{
	ImGui::EndGroup();
}

void TestScene::Update([[maybe_unused]] const f32 dT)
{
	auto& io = ImGui::GetIO();
	m_pFPSText->SetText(std::to_string(m_pFPSComponent->GetFPS()));
	ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

	ImGui::Separator();
}
