#pragma once
#include "Components/BaseComponent.h"
#include "Graphics/GLTextureWrapper.h"
class RenderComponent final : public BaseComponent
{
public:
	RenderComponent() = default;
	virtual ~RenderComponent() override;
	DEL_ROF(RenderComponent)

	void Update([[maybe_unused]] f32 dT) override;
	void AddTexture(GLTextureWrapper* pTexture) noexcept { m_RenderBuffer.emplace(std::make_pair(pTexture->GetRenderPriority(), pTexture)); }


	void Render() const;
	void ClearBuffer();
protected:
	void Initialize() override;

private:
	std::multimap<u32, GLTextureWrapper*> m_RenderBuffer;
};
