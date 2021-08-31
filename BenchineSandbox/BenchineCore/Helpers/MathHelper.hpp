#pragma once
#include <numeric>
#include "Core/CoreTypes.hpp"

namespace MathHelper
{
	[[nodiscard]] inline auto PolyCenter(const Polygon2D& polygon) noexcept -> glm::vec2
	{
		const auto vertexSum = std::accumulate(polygon.cbegin(), polygon.cend(), glm::vec2(), [] (const glm::vec2& v1, const glm::vec2& v2) { return v1 + v2; });
		return glm::vec2(vertexSum.x / static_cast<f32>(polygon.size()), vertexSum.y / static_cast<f32>(polygon.size()));
	}
}
