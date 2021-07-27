#pragma once
#include "Components/BaseComponent.h"
#include <functional>
#include "Helpers/GeneralHelpers.hpp"
#include "Helpers/Sat.hpp"

enum class CollisionMode
{
	Static,
	Dynamic,
	Trigger
};

using CollisionCallback = std::function<void(PolygonCollisionResult, PhysicsComponent2D*, PhysicsComponent2D*)>;

class PhysicsComponent2D final : public BaseComponent
{
public:
	explicit PhysicsComponent2D(CollisionMode collisionMode = CollisionMode::Static);

	[[nodiscard]] constexpr auto GetVelocity() const noexcept -> glm::vec2 { return m_Velocity; }
	[[nodiscard]] constexpr auto GetBaseCollider() const noexcept -> const Collider2D& { return m_BaseCollider; }
	[[nodiscard]] constexpr auto GetCollider() const noexcept -> const Collider2D& { return m_Collider; }
	[[nodiscard]] constexpr auto GetCollisionMode() const noexcept -> CollisionMode { return m_CollisionMode; }
	[[nodiscard]] constexpr auto IsOnGround() const noexcept -> bool { return m_IsOnGround; }
	void SetCollider(const Collider2D& collider) noexcept
	{
		m_BaseCollider = collider;
		m_Collider = collider;
	}
	void SetVelocity(const glm::vec2& velocity) noexcept { m_Velocity = velocity; }
	void SetCallback(const CollisionCallback callback, const bool callbackOverride = false) noexcept
	{
		m_PhysicsCallback = callback;
		m_CallBackOverriden = callbackOverride;
	}
	void HandleCollision(PhysicsComponent2D* pOtherComponent);

protected:
	void Initialize() override;
	void Update([[maybe_unused]] f32 dT) override;

private:

	CollisionMode m_CollisionMode;
	CollisionCallback m_PhysicsCallback;
	bool m_CallBackOverriden;
	glm::vec2 m_Velocity;
	Collider2D m_Collider;
	Collider2D m_BaseCollider;
	bool m_IsOnGround;
};
