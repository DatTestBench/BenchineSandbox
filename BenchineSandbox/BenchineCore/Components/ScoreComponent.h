#pragma once
#include "Components/BaseComponent.h"

class ScoreComponent final : public BaseComponent
{
public:
    ScoreComponent();
    virtual ~ScoreComponent() override = default;
    DEL_ROF(ScoreComponent)

    [[nodiscard]] constexpr auto GetScore() const noexcept-> uint32_t { return m_Score; }
    void AddScore(uint32_t score) { m_Score += score; }
protected:
    void Initialize() override;

private:
    uint32_t m_Score;
};