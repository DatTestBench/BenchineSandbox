#pragma once
#include "Helpers/GeneralHelpers.hpp"

#ifdef _DEBUG
#define DEBUGRENDER(func) DebugRenderer::func;
#else
#define DEBUGRENDER(func) do{}while(0);
#endif

namespace DebugRenderer
{
	//POINTS
	void DrawPoint(f32 x, f32 y, f32 pointSize = 1.0f);
	void DrawPoint(const glm::vec2& p, f32 pointSize = 1.0f);
	void DrawPoints(const std::vector<glm::vec2>& vertices, f32 pointSize = 1.0f);
	//LINES
	void DrawLine(f32 x1, f32 y1, f32 x2, f32 y2, f32 lineWidth = 1.0f);
	void DrawLine(const glm::vec2& start, const glm::vec2& end, f32 lineWidth = 1.0f);
	//RECTS
	void DrawRect(f32 left, f32 bottom, f32 width, f32 height, f32 lineWidth = 1.0f);
	void DrawRect(const glm::vec2& bottomLeft, f32 width, f32 height, f32 lineWidth = 1.0f);
	void DrawRect(const FRect& rect, f32 lineWidth = 1.0f);
	void FillRect(f32 left, f32 bottom, f32 width, f32 height);
	void FillRect(const glm::vec2& bottomLeft, f32 width, f32 height);
	void FillRect(const FRect& rect);
	/*Centered*/
	void DrawRectC(f32 x, f32 y, f32 width, f32 height, f32 lineWidth = 1.0f);
	void DrawRectC(const glm::vec2& center, f32 width, f32 height, f32 lineWidth = 1.0f);
	void DrawRectC(const FRect& rect, f32 lineWidth = 1.0f);
	void FillRectC(f32 x, f32 y, f32 width, f32 height);
	void FillRectC(const glm::vec2& center, f32 width, f32 height);
	void FillRectC(const FRect& rect);
	//CIRCLES
	void DrawEllipse(f32 centerX, f32 centerY, f32 radX, f32 radY, f32 lineWidth = 1.0f);
	void DrawEllipse(const glm::vec2& center, f32 radX, f32 radY, f32 lineWidth = 1.0f);
	void DrawEllipse(const FEllipse& ellipse, f32 lineWidth = 1.0f);
	void FillEllipse(f32 centerX, f32 centerY, f32 radX, f32 radY);
	void FillEllipse(const FEllipse& ellipse);
	void FillEllipse(const glm::vec2& center, f32 radX, f32 radY);
	//ARCS
	void DrawArc(f32 centerX, f32 centerY, f32 radX, f32 radY, f32 fromAngle, f32 tillAngle, f32 lineWidth = 1.0f);
	void DrawArc(const glm::vec2& center, f32 radX, f32 radY, f32 fromAngle, f32 tillAngle, f32 lineWidth = 1.0f);
	void FillArc(f32 centerX, f32 centerY, f32 radX, f32 radY, f32 fromAngle, f32 tillAngle);
	void FillArc(const glm::vec2& center, f32 radX, f32 radY, f32 fromAngle, f32 tillAngle);
	//POLYGONS
	void DrawPolygon(const Polygon2D& vertices, bool closed = true, f32 lineWidth = 1.0f);
	void FillPolygon(const Polygon2D& vertices);
}