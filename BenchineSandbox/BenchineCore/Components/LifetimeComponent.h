#pragma once
#include "Components/BaseComponent.h"

class LifetimeComponent final : public BaseComponent
{
public:
	explicit LifetimeComponent(f32 lifeTime);

	void Update(f32 dT) override;

protected:
	void Initialize() override;

private:
	f32 m_LifeTime;
};
