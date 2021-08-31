#pragma once
#include "Components/BaseComponent.h"

#include <map>

#include "Graphics/GLTextureWrapper.h"
class RenderComponent final : public BaseComponent
{
public:
	~RenderComponent() override;

	void Update(f32 dT) override;
	void AddTexture(GLTextureWrapper* pTexture) noexcept { m_RenderBuffer.emplace(pTexture->GetRenderPriority(), pTexture); }

	void Render() const;
	void ClearBuffer();
protected:
	void Initialize() override;

private:
	std::multimap<u32, GLTextureWrapper*> m_RenderBuffer;
};
