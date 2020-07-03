#include "BenchinePCH.h"
#include "Components/TextureComponent.h"
#include "Components/RenderComponent.h"

TextureComponent::TextureComponent(Texture2D* pTexture)
    : m_pTexture(pTexture)
{

}

void TextureComponent::Initialize()
{

}


void TextureComponent::Update(float)
{
    GetGameObject()->GetRenderComponent()->AddTexture(m_pTexture->GetTextureWrapper());
}