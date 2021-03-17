#pragma once
#include "Components/BaseComponent.h"

class BubbleComponent final : public BaseComponent
{
public:
	BubbleComponent(const glm::vec2& throwDirection);
	virtual ~BubbleComponent() override = default;
	DEL_ROF(BubbleComponent)

	void Update(f32 dT) override;


protected:
	void Initialize() override;

private:

	glm::vec2 m_Velocity;
};
