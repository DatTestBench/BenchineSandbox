#pragma once
#include <glm/vec2.hpp>

#include "Core/CoreTypes.hpp"

namespace CollisionHelper
{
	[[nodiscard]] constexpr auto IsPointInFRect(const glm::vec2& p, const FRect& r) noexcept -> bool
	{
		return p.x >= r.Pos.x
		&& p.x <= r.Pos.x + r.Width
		&& p.y >= r.Pos.y
		&& p.y <= r.Pos.y + r.Height;
	}
}
