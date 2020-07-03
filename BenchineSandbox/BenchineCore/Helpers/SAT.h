#pragma once
#include "Helpers/GeneralHelpers.h"

//Adapted from : https://www.codeproject.com/Articles/15573/2D-Polygon-Collision-Detection
//				 http://www.dyn4j.org/2010/01/sat/

class PhysicsComponent2D;
// Structure that stores the results of the PolygonCollision function
struct PolygonCollisionResult
{
	// Are the polygons currently intersecting?
	bool intersect;
	// The translation to apply to the first polygon to push the polygons apart.
	glm::vec2 minimumTranslationVector;
};

namespace sat
{
	PolygonCollisionResult PolygonCollision(PhysicsComponent2D* pActorA, PhysicsComponent2D* pActorB);
	PolygonCollisionResult PolygonCollision(PhysicsComponent2D* pActor, const Collider2D& staticPoly);
	// Maps the polygon min / max bounds onto an axis
	Projection2D ProjectPolygon(const glm::vec2& axis, const Collider2D& vertexSet);
	float IntervalDistance(const Projection2D& projectionA, const Projection2D& projectionB);
	glm::vec2 MakeAxis(const glm::vec2& vertexA, const glm::vec2& vertexB);
}