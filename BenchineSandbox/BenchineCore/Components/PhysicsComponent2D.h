#pragma once
#include "Components/BaseComponent.h"
#include "Helpers/Sat.h"
#include "Helpers/GeneralHelpers.h"
#include "Debugging/DebugRenderer.h"
#include <functional>
enum class CollisionMode
{
	STATIC,
	DYNAMIC,
	TRIGGER
};

class PhysicsComponent2D final : public BaseComponent
{
public:
	PhysicsComponent2D(CollisionMode collisionMode = CollisionMode::STATIC);
	virtual ~PhysicsComponent2D() override;
	DEL_ROF(PhysicsComponent2D)

	[[nodiscard]] constexpr auto GetVelocity() const noexcept-> glm::vec2 { return m_Velocity; }
	[[nodiscard]] constexpr auto GetBaseCollider() const noexcept-> const Collider2D& { return m_BaseCollider; }
	[[nodiscard]] constexpr auto GetCollider() const noexcept-> const Collider2D& { return m_Collider; }
	[[nodiscard]] constexpr auto GetCollisionMode() const noexcept-> CollisionMode { return m_CollisionMode; }
	[[nodiscard]] constexpr auto IsOnGround() const noexcept-> bool { return m_IsOnGround; }
	void SetCollider(const Collider2D& collider) noexcept { m_BaseCollider = collider; m_Collider = collider; }
	void SetVelocity(const glm::vec2& velocity) noexcept { m_Velocity = velocity; }
	void SetCallback(std::function<void(PolygonCollisionResult, PhysicsComponent2D*, PhysicsComponent2D*)> callback, bool callbackOverride = false) noexcept { m_PhysicsCallback = callback; m_CallBackOverriden = callbackOverride; }
	void HandleCollision(PhysicsComponent2D* pOtherActor);

protected:
	void Initialize() override;
	void Update([[maybe_unused]] float dT) override;

private:

	CollisionMode m_CollisionMode;
	std::function<void(PolygonCollisionResult, PhysicsComponent2D*, PhysicsComponent2D*)> m_PhysicsCallback;
	bool m_CallBackOverriden;
	glm::vec2 m_Velocity;
	Collider2D m_Collider;
	Collider2D m_BaseCollider;
	bool m_IsOnGround;


};