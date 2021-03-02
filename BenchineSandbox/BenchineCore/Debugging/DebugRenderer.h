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
	void DrawPoint(float x, float y, float pointSize = 1.0f);
	void DrawPoint(const glm::vec2& p, float pointSize = 1.0f);
	void DrawPoints(const std::vector<glm::vec2>& vertices, float pointSize = 1.0f);
	//LINES
	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth = 1.0f);
	void DrawLine(const glm::vec2& start, const glm::vec2& end, float lineWidth = 1.0f);
	//RECTS
	void DrawRect(float left, float bottom, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const glm::vec2& bottomLeft, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const FRect& rect, float lineWidth = 1.0f);
	void FillRect(float left, float bottom, float width, float height);
	void FillRect(const glm::vec2& bottomLeft, float width, float height);
	void FillRect(const FRect& rect);
	/*Centered*/
	void DrawRectC(float x, float y, float width, float height, float lineWidth = 1.0f);
	void DrawRectC(const glm::vec2& center, float width, float height, float lineWidth = 1.0f);
	void DrawRectC(const FRect& rect, float lineWidth = 1.0f);
	void FillRectC(float x, float y, float width, float height);
	void FillRectC(const glm::vec2& center, float width, float height);
	void FillRectC(const FRect& rect);
	//CIRCLES
	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const glm::vec2& center, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const FEllipse& ellipse, float lineWidth = 1.0f);
	void FillEllipse(float centerX, float centerY, float radX, float radY);
	void FillEllipse(const FEllipse& ellipse);
	void FillEllipse(const glm::vec2& center, float radX, float radY);
	//ARCS
	void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	void DrawArc(const glm::vec2& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle);
	void FillArc(const glm::vec2& center, float radX, float radY, float fromAngle, float tillAngle);
	//POLYGONS
	void DrawPolygon(const Polygon2D& vertices, bool closed = true, float lineWidth = 1.0f);
	void FillPolygon(const Polygon2D& vertices);
}