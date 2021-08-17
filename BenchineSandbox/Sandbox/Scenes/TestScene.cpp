#include "SandboxPCH.h"
#include "Scenes/TestScene.h"

#include "NodeEditor/BNEditor.h"
#include "NodeEditor/BNNodes.h"
#include "Resources/Font.h"

struct LinkInfo
{
};

TestScene::TestScene(const std::string_view& sceneName)
	: Scene(sceneName)
	, m_pFPSCounter(nullptr)
	, m_pFPSComponent(nullptr)
	, m_pFPSText(nullptr)
	, m_Editor("TestEditor")
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
	m_pFPSText->GetTexture()->SetOffsetMode(TextureOffsetMode::Topleft);
	m_pFPSText->GetTexture()->SetRenderPriority(10U);

	m_Editor.AddNode(new Nodes::DummyNode("Test1"));
	m_Editor.AddNode(new Nodes::DummyNode("Test2"));
	m_Editor.AddNode(new Nodes::DummyNode("Test3"));
	m_Editor.AddNode(new Nodes::DummyNode("Test4"));

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

void TestScene::Update(const f32 dT)
{
	m_pFPSText->SetText(std::to_string(m_pFPSComponent->GetFPS()));

	m_Editor.Update(dT);	
}
