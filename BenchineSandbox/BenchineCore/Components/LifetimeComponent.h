#pragma once
#include "Components/BaseComponent.h"

class LifetimeComponent final : public BaseComponent
{
public:
    LifetimeComponent(float lifeTime);
    virtual ~LifetimeComponent() override = default;
    DEL_ROF(LifetimeComponent)

    void Update(float dT) override;

protected:
    void Initialize() override;

private:
    float m_LifeTime;
};