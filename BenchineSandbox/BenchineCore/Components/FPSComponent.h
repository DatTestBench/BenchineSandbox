#pragma once
#include "Components/BaseComponent.h"
class FPSComponent final : public BaseComponent
{
public:
	FPSComponent();
	virtual ~FPSComponent() override = default;
	DEL_ROF(FPSComponent)

	void Update([[maybe_unused]] float dT) override;

	[[nodiscard]] constexpr auto GetFPS() const noexcept-> float { return m_FPS; }

protected:
	void Initialize() override;

private:
	float m_FPS;
};

