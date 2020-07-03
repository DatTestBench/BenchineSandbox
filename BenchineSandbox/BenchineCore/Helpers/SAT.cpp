#include "BenchinePCH.h"
#include "Helpers/SAT.h"
#include "Components/PhysicsComponent2D.h"
#include "Components/TransformComponent.h"
#include "glm/geometric.hpp"

// Collision for GameObjects
PolygonCollisionResult sat::PolygonCollision(PhysicsComponent2D* pActorA, PhysicsComponent2D* pActorB)
{
	PolygonCollisionResult result{};
	result.intersect = true;

	const auto& colliderA = pActorA->GetCollider(); 
	const auto& colliderB = pActorB->GetCollider();
	size_t vertexCountA = colliderA.size();
	size_t vertexCountB = colliderB.size();

	float minIntervalDistance = std::numeric_limits<float>::infinity();
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

		// Check if the polygon projections are currentlty intersecting
		if (IntervalDistance(projectionA, projectionB) > 0)
		{
			result.intersect = false;
		}

		// If the polygon does not intersect, exit the loop
		if (!result.intersect)
			break;

		// Check if the current interval distance is the minimum one. If so store
		// the interval distance and the current distance.
		// This will be used to calculate the minimum translation vector
		float intervalDistance = abs(IntervalDistance(projectionA, projectionB));
		if (intervalDistance < minIntervalDistance)
		{
			minIntervalDistance = intervalDistance;
			translationAxis = axis;

			glm::vec2 delta = MathHelper::PolyCenter(colliderA) - MathHelper::PolyCenter(colliderB);
			if (glm::dot(delta, translationAxis) < 0)
				translationAxis = -translationAxis;
		}
	}

	// The minimum translation vector
	// can be used to push the polygons appart.
	if (result.intersect)
		result.minimumTranslationVector = translationAxis * minIntervalDistance;

	return result;
}


// Collision for GameObject to static collider
PolygonCollisionResult sat::PolygonCollision(PhysicsComponent2D* pActor, const Collider2D& staticPoly)
{
	//glm::vec2 velocityDelta = pActor->GetVelocity();

	PolygonCollisionResult result{};
	result.intersect = true;

	const auto& collider = pActor->GetCollider();

	size_t vertexCountA = collider.size();
	size_t vertexCountB = staticPoly.size();
	float minIntervalDistance = std::numeric_limits<float>::infinity();
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

		// Check if the polygon projections are currentlty intersecting
		if (IntervalDistance(projectionA, projectionB) > 0)
		{
			result.intersect = false;
			// If the polygon does not intersect, exit the loop
			break;
		}

		// Check if the current interval distance is the minimum one. If so store
		// the interval distance and the current distance.
		// This will be used to calculate the minimum translation vector
		float intervalDistance = abs(IntervalDistance(projectionA, projectionB));
		if (intervalDistance < minIntervalDistance)
		{
			minIntervalDistance = intervalDistance;
			translationAxis = axis;
			
			glm::vec2 delta = MathHelper::PolyCenter(collider) - MathHelper::PolyCenter(staticPoly);
			if (glm::dot(delta, translationAxis) < 0)
				translationAxis = -translationAxis;
		}
	}

	// The minimum translation vector
	// can be used to push the polygons appart.
	if (result.intersect)
		result.minimumTranslationVector = translationAxis * minIntervalDistance;

	return result;
}


Projection2D sat::ProjectPolygon(const glm::vec2& axis, const Collider2D& polygon)
{
	// To project a point on an axis use the dot product
	float dotProduct = glm::dot(axis, polygon.at(0));
	Projection2D projectionBounds{dotProduct};
	for (size_t i = 0; i < polygon.size(); ++i)
	{
		dotProduct = glm::dot(axis, polygon.at(i));
		if (dotProduct < projectionBounds.Min)
			projectionBounds.Min = dotProduct;
		else if (dotProduct > projectionBounds.Max)
			projectionBounds.Max = dotProduct;
	}
	return projectionBounds;
}

float sat::IntervalDistance(const Projection2D& projectionA, const Projection2D& projectionB)
{
	if (projectionA.Min < projectionB.Min)
		return projectionB.Min - projectionA.Max;
	else
		return projectionA.Min - projectionB.Max;
}

glm::vec2 sat::MakeAxis(const glm::vec2& vertexA, const glm::vec2& vertexB)
{
	// Get edge
	const glm::vec2 edge = vertexB - vertexA;
	// get either perpendicular vector
	const glm::vec2 normal{ -edge.y, edge.x };
	//return normalized
	return glm::normalize(normal);
}