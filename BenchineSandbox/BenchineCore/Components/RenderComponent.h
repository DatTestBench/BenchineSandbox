#pragma once
#include "Components/BaseComponent.h"
#include "Graphics/GLTextureWrapper.h"
class RenderComponent final : public BaseComponent
{
public:
	RenderComponent();
	virtual ~RenderComponent() override;
	DEL_ROF(RenderComponent)

	void Update([[maybe_unused]] float dT) override;
	void AddTexture(GLTextureWrapper* pTexture) noexcept { m_RenderBuffer.emplace(std::make_pair(pTexture->GetRenderPriority(), pTexture)); }


	void Render() const;
	void ClearBuffer();
protected:
	void Initialize() override;

private:
	std::multimap<uint32_t, GLTextureWrapper*> m_RenderBuffer;
};