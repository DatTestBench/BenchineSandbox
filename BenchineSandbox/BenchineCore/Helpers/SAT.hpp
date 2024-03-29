#pragma once
#include <glm/vec2.hpp>

#include "Core/CoreTypes.hpp"
//Adapted from : https://www.codeproject.com/Articles/15573/2D-Polygon-Collision-Detection
//				 http://www.dyn4j.org/2010/01/sat/

class PhysicsComponent2D;
// Structure that stores the results of the PolygonCollision function
struct PolygonCollisionResult
{
	// Are the polygons currently intersecting?
	bool Intersect;
	// The translation to apply to the first polygon to push the polygons apart.
	glm::vec2 MinimumTranslationVector;
};

namespace sat
{
	PolygonCollisionResult PolygonCollision(const PhysicsComponent2D* pActorA, const PhysicsComponent2D* pActorB);
	PolygonCollisionResult PolygonCollision(const PhysicsComponent2D* pActor, const Collider2D& staticPoly);
	// Maps the polygon min / max bounds onto an axis
	Projection2D ProjectPolygon(const glm::vec2& axis, const Collider2D& polygon);
	f32 IntervalDistance(const Projection2D& projectionA, const Projection2D& projectionB);
	glm::vec2 MakeAxis(const glm::vec2& vertexA, const glm::vec2& vertexB);
}
