#pragma once
#include "Components/BaseComponent.h"
#include "glm/glm.hpp"
class TransformComponent final : public BaseComponent
{
public:
	TransformComponent() = default;
	explicit TransformComponent(const glm::vec3& pos, const glm::vec2& scale);

	void SetPosition(f32 x, f32 y, f32 z = 1.f) noexcept;
	void Move(f32 x, f32 y, f32 z) noexcept;
	void Move(const glm::vec2& movementVec) noexcept;
	void SetScale(const glm::vec2& scale) noexcept;

	[[nodiscard]] constexpr auto GetPosition() const noexcept -> glm::vec3 { return m_Position; }
	[[nodiscard]] constexpr auto GetScale() const noexcept -> glm::vec2 { return m_Scale; }

protected:
	void Initialize() override;
	void Update(f32 dT) override;
private:
	glm::vec3 m_Position = { 0.f, 0.f, 1.f };
	glm::vec2 m_Scale = { 1.f, 1.f };
};
