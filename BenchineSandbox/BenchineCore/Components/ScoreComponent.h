#pragma once
#include "Components/BaseComponent.h"

class ScoreComponent final : public BaseComponent
{
public:
	ScoreComponent();
	virtual ~ScoreComponent() override = default;
	DEL_ROF(ScoreComponent)

	[[nodiscard]] constexpr auto GetScore() const noexcept -> u32 { return m_Score; }
	void AddScore(const u32 score) { m_Score += score; }
protected:
	void Initialize() override;

private:
	u32 m_Score;
};
