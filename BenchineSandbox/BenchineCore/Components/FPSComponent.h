#pragma once
#include "Components/BaseComponent.h"
class FPSComponent final : public BaseComponent
{
public:
	FPSComponent();
	virtual ~FPSComponent() override = default;
	DEL_ROF(FPSComponent)

	void Update([[maybe_unused]] f32 dT) override;

	[[nodiscard]] constexpr auto GetFPS() const noexcept -> f32 { return m_FPS; }

protected:
	void Initialize() override;

private:
	f32 m_FPS;
};
