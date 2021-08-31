#pragma once
#include "Components/BaseComponent.h"

class FPSComponent final : public BaseComponent
{
public:
	void Update(f32 dT) override;

	[[nodiscard]] constexpr auto GetFPS() const noexcept -> f32 { return m_FPS; }

protected:
	void Initialize() override;

private:
	f32 m_FPS = {};
};
