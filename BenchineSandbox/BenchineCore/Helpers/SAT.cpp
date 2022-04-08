#include "Helpers/SAT.hpp"

#include "MathHelper.hpp"
#include "Components/PhysicsComponent2D.h"

#include "Core/Benchine.h"

// TODO: see if the following could be merged into one function that calls the other
// Collision for GameObjects
PolygonCollisionResult sat::PolygonCollision(const PhysicsComponent2D* pActorA, const PhysicsComponent2D* pActorB)
{
	PolygonCollisionResult result{};
	result.Intersect = true;

	const auto& colliderA = pActorA->GetCollider();
	const auto& colliderB = pActorB->GetCollider();
	const auto vertexCountA = colliderA.size();
	const auto vertexCountB = colliderB.size();

	auto minIntervalDistance = std::numeric_limits<f32>::infinity();
	glm::vec2 translationAxis{}, currentVertex{}, nextVertex{};

	// Loop through all the vertices of both polygons
	for (size_t vertexIndex = 0; vertexIndex < vertexCountA + vertexCountB; ++vertexIndex)
	{
		if (vertexIndex < vertexCountA)
		{
			currentVertex = colliderA.at(vertexIndex);
			nextVertex = colliderA.at(vertexIndex + 1 == vertexCountA ? 0 : vertexIndex + 1);
		}
		else
		{
			currentVertex = colliderB.at(vertexIndex - vertexCountA);
			nextVertex = colliderB.at(vertexIndex - vertexCountA + 1 == vertexCountB ? 0 : vertexIndex - vertexCountA + 1);
		}

		// ===== 1. Find if the polygons are currently intersecting =====

		// Find the axis perpendicular to the current edge (vertexpair)s
		const auto axis = MakeAxis(currentVertex, nextVertex);

		// Find the projection of the polygon on the current axis
		const auto projectionA = ProjectPolygon(axis, colliderA);
		const auto projectionB = ProjectPolygon(axis, colliderB);

		// Check if the polygon projections are currently intersecting
		if (IntervalDistance(projectionA, projectionB) > 0)
		{
			result.Intersect = false;
		}

		// If the polygon does not intersect, exit the loop
		if (!result.Intersect)
			break;

		// Check if the current interval distance is the minimum one. If so store
		// the interval distance and the current distance.
		// This will be used to calculate the minimum translation vector
		const f32 intervalDistance = abs(IntervalDistance(projectionA, projectionB));
		if (intervalDistance < minIntervalDistance)
		{
			minIntervalDistance = intervalDistance;
			translationAxis = axis;

			const glm::vec2 delta = MathHelper::PolyCenter(colliderA) - MathHelper::PolyCenter(colliderB);
			if (dot(delta, translationAxis) < 0)
				translationAxis = -translationAxis;
		}
	}

	// The minimum translation vector
	// can be used to push the polygons apart.
	if (result.Intersect)
		result.MinimumTranslationVector = translationAxis * minIntervalDistance;

	return result;
}


// Collision for GameObject to static collider
PolygonCollisionResult sat::PolygonCollision(const PhysicsComponent2D* pActor, const Collider2D& staticPoly)
{
	//glm::vec2 velocityDelta = pActor->GetVelocity();

	PolygonCollisionResult result{};
	result.Intersect = true;

	const auto& collider = pActor->GetCollider();

	const size_t vertexCountA = collider.size();
	const size_t vertexCountB = staticPoly.size();
	f32 minIntervalDistance = std::numeric_limits<f32>::infinity();
	glm::vec2 translationAxis{}, currentVertex{}, nextVertex{};

	// Loop through all the vertices of both polygons
	for (size_t vertexIndex = 0; vertexIndex < vertexCountA + vertexCountB; ++vertexIndex)
	{
		if (vertexIndex < vertexCountA)
		{
			currentVertex = collider.at(vertexIndex);
			nextVertex = collider.at(vertexIndex + 1 == vertexCountA ? 0 : vertexIndex + 1);
		}
		else
		{
			currentVertex = staticPoly.at(vertexIndex - vertexCountA);
			nextVertex = staticPoly.at(vertexIndex - vertexCountA + 1 == vertexCountA ? 0 : vertexIndex - vertexCountA + 1);
		}

		// ===== 1. Find if the polygons are currently intersecting =====

		// Find the axis perpendicular to the current edge (vertexpair)s
		const auto axis = MakeAxis(currentVertex, nextVertex);

		// Find the projection of the polygon on the current axis
		const auto projectionA = ProjectPolygon(axis, collider);
		const auto projectionB = ProjectPolygon(axis, staticPoly);

		// Check if the polygon projections are currently intersecting
		if (IntervalDistance(projectionA, projectionB) > 0)
		{
			result.Intersect = false;
			// If the polygon does not intersect, exit the loop
			break;
		}

		// Check if the current interval distance is the minimum one. If so store
		// the interval distance and the current distance.
		// This will be used to calculate the minimum translation vector
		const f32 intervalDistance = glm::abs(IntervalDistance(projectionA, projectionB));
		if (intervalDistance < minIntervalDistance)
		{
			minIntervalDistance = intervalDistance;
			translationAxis = axis;

			const glm::vec2 delta = MathHelper::PolyCenter(collider) - MathHelper::PolyCenter(staticPoly);
			if (dot(delta, translationAxis) < 0)
				translationAxis = -translationAxis;
		}
	}

	// The minimum translation vector
	// can be used to push the polygons apart.
	if (result.Intersect)
		result.MinimumTranslationVector = translationAxis * minIntervalDistance;

	return result;
}

Projection2D sat::ProjectPolygon(const glm::vec2& axis, const Collider2D& polygon)
{
	// To project a point on an axis use the dot product
	Projection2D projectionBounds{ std::numeric_limits<f32>::max(), std::numeric_limits<f32>::min() };
	for (const auto& vertex : polygon)
	{
		const f32 dotProduct = dot(axis, vertex);
		projectionBounds.Min = std::min(projectionBounds.Min, dotProduct);
		projectionBounds.Max = std::max(projectionBounds.Max, dotProduct);
	}
	return projectionBounds;
}

f32 sat::IntervalDistance(const Projection2D& projectionA, const Projection2D& projectionB)
{
	if (projectionA.Min < projectionB.Min)
		return projectionB.Min - projectionA.Max;
	return projectionA.Min - projectionB.Max;
}

glm::vec2 sat::MakeAxis(const glm::vec2& vertexA, const glm::vec2& vertexB)
{
	// Get edge
	const glm::vec2 edge = vertexB - vertexA;
	// get either perpendicular vector
	const glm::vec2 normal{ -edge.y, edge.x };
	//return normalized
	return normalize(normal);
}
