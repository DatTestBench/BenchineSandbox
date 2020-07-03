#pragma once
#include "Helpers/GeneralHelpers.h"

#ifdef _DEBUG
#define DEBUGRENDER(func) DebugRenderer::func;
#else
#define DEBUGRENDER(func) do{}while(0);
#endif

namespace DebugRenderer
{
	//POINTS
	void DrawPoint(const float x, const float y, const float pointSize = 1.0f);
	void DrawPoint(const glm::vec2& p, const float pointSize = 1.0f);
	void DrawPoints(const std::vector<glm::vec2>& vertices, const float pointSize = 1.0f);
	//LINES
	void DrawLine(const float x1, const float y1, const float x2, const float y2, const float lineWidth = 1.0f);
	void DrawLine(const glm::vec2& p1, const glm::vec2& p2, const float lineWidth = 1.0f);
	//RECTS
	void DrawRect(const float left, const float bottom, const float width, const float height, const float lineWidth = 1.0f);
	void DrawRect(const glm::vec2& bottomLeft, const float width, const float height, const float lineWidth = 1.0f);
	void DrawRect(const FRect& rect, const float lineWidth = 1.0f);
	void FillRect(const float left, const float bottom, const float width, const float height);
	void FillRect(const glm::vec2& bottomLeft, const float width, const float height);
	void FillRect(const FRect& rect);
	/*Centered*/
	void DrawRectC(const float x, const float y, const float width, const float height, const float lineWidth = 1.0f);
	void DrawRectC(const glm::vec2& center, const float width, const float height, const float lineWidth = 1.0f);
	void DrawRectC(const FRect& rect, const float lineWidth = 1.0f);
	void FillRectC(const float x, const float y, const float width, const float height);
	void FillRectC(const glm::vec2& center, const float width, const float height);
	void FillRectC(const FRect& rect);
	//CIRCLES
	void DrawEllipse(const float centerX, const float centerY, const float radX, const float radY, const float lineWidth = 1.0f);
	void DrawEllipse(const glm::vec2& center, const float radX, const float radY, const float lineWidth = 1.0f);
	void DrawEllipse(const FEllipse& ellipse, const float lineWidth = 1.0f);
	void FillEllipse(const float centerX, const float centerY, const float radX, const float radY);
	void FillEllipse(const FEllipse& ellipse);
	void FillEllipse(const glm::vec2& center, const float radX, const float radY);
	//ARCS
	void DrawArc(const float centerX, const float centerY, const float radX, const float radY, const float fromAngle, const float tillAngle, const float lineWidth = 1.0f);
	void DrawArc(const glm::vec2& center, const float radX, const float radY, const float fromAngle, const float tillAngle, const float lineWidth = 1.0f);
	void FillArc(const float centerX, const float centerY, const float radX, const float radY, const float fromAngle, const float tillAngle);
	void FillArc(const glm::vec2& center, const float radX, const float radY, const float fromAngle, const float tillAngle);
	//POLYGONS
	void DrawPolygon(const Polygon2D& vertices, const bool closed = true, const float lineWidth = 1.0f);
	void FillPolygon(const Polygon2D& vertices);
}