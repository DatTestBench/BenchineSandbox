#include "BenchinePCH.h"
#include "Debugging/DebugRenderer.h"
#include <glm/gtc/constants.hpp>

//POINTS
#pragma region Points
void DebugRenderer::DrawPoint(const f32 x, const f32 y, const f32 pointSize)
{
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	{
		glVertex3f(x, y, 1.f);
	}
	glEnd();
}

void DebugRenderer::DrawPoint(const glm::vec2& p, const f32 pointSize)
{
	DrawPoint(p.x, p.y, pointSize);
}

void DebugRenderer::DrawPoints(const std::vector<glm::vec2>& vertices, const f32 pointSize)
{
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	{
		for (auto [x, y] : vertices)
		{
			glVertex3f(x, y, 1.f);
		}
	}
	glEnd();
}
#pragma endregion Points

//LINES
#pragma region Lines
void DebugRenderer::DrawLine(const glm::vec2& start, const glm::vec2& end, const f32 lineWidth)
{
	DrawLine(start.x, start.y, end.x, end.y, lineWidth);
}

void DebugRenderer::DrawLine(const f32 x1, const f32 y1, const f32 x2, const f32 y2, const f32 lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	{
		glVertex3f(x1, y1, 1.f);
		glVertex3f(x2, y2, 1.f);
	}
	glEnd();
}
#pragma endregion Lines

//RECTS
#pragma region Rects
void DebugRenderer::DrawRect(const FRect& rect, const f32 lineWidth)
{
	DrawRect(rect.Pos.x, rect.Pos.y, rect.Width, rect.Height, lineWidth);
}

void DebugRenderer::DrawRect(const glm::vec2& bottomLeft, const f32 width, const f32 height, const f32 lineWidth)
{
	DrawRect(bottomLeft.x, bottomLeft.y, width, height, lineWidth);
}

void DebugRenderer::DrawRect(const f32 left, const f32 bottom, const f32 width, const f32 height, const f32 lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(left, bottom, 1.f);
		glVertex3f(left + width, bottom, 1.f);
		glVertex3f(left + width, bottom + height, 1.f);
		glVertex3f(left, bottom + height, 1.f);
	}
	glEnd();
}

void DebugRenderer::FillRect(const FRect& rect)
{
	FillRect(rect.Pos.x, rect.Pos.y, rect.Width, rect.Height);
}

void DebugRenderer::FillRect(const glm::vec2& bottomLeft, const f32 width, const f32 height)
{
	FillRect(bottomLeft.x, bottomLeft.y, width, height);
}

void DebugRenderer::FillRect(const f32 left, const f32 bottom, const f32 width, const f32 height)
{
	glBegin(GL_POLYGON);
	{
		glVertex3f(left, bottom, 1.f);
		glVertex3f(left + width, bottom, 1.f);
		glVertex3f(left + width, bottom + height, 1.f);
		glVertex3f(left, bottom + height, 1.f);
	}
	glEnd();
}

/*Centered*/
void DebugRenderer::DrawRectC(const FRect& rect, const f32 lineWidth)
{
	DrawRect(rect.Pos.x, rect.Pos.y, rect.Width, rect.Height, lineWidth);
}

void DebugRenderer::DrawRectC(const glm::vec2& center, const f32 width, const f32 height, const f32 lineWidth)
{
	DrawRect(center.x, center.y, width, height, lineWidth);
}

void DebugRenderer::DrawRectC(const f32 x, const f32 y, const f32 width, const f32 height, const f32 lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(x - width / 2.f, y - height / 2.f, 1.f);
		glVertex3f(x + width / 2.f, y - height / 2.f, 1.f);
		glVertex3f(x + width / 2.f, y + height / 2.f, 1.f);
		glVertex3f(x - width / 2.f, y + height / 2.f, 1.f);
	}
	glEnd();
}

void DebugRenderer::FillRectC(const FRect& rect)
{
	FillRect(rect.Pos.x, rect.Pos.y, rect.Width, rect.Height);
}

void DebugRenderer::FillRectC(const glm::vec2& center, const f32 width, const f32 height)
{
	FillRect(center.x, center.y, width, height);
}

void DebugRenderer::FillRectC(const f32 x, const f32 y, const f32 width, const f32 height)
{
	glBegin(GL_POLYGON);
	{
		glVertex3f(x - width / 2.f, y - height / 2.f, 1.f);
		glVertex3f(x + width / 2.f, y - height / 2.f, 1.f);
		glVertex3f(x + width / 2.f, y + height / 2.f, 1.f);
		glVertex3f(x - width / 2.f, y + height / 2.f, 1.f);
	}
	glEnd();
}
#pragma endregion Rects

//CIRCLES
#pragma region Circles
void DebugRenderer::DrawEllipse(const FEllipse& ellipse, const f32 lineWidth)
{
	DrawEllipse(ellipse.Center.x, ellipse.Center.y, ellipse.RadX, ellipse.RadY, lineWidth);
}

void DebugRenderer::DrawEllipse(const glm::vec2& center, const f32 radX, const f32 radY, const f32 lineWidth)
{
	DrawEllipse(center.x, center.y, radX, radY, lineWidth);
}

void DebugRenderer::DrawEllipse(const f32 centerX, const f32 centerY, const f32 radX, const f32 radY, const f32 lineWidth)
{
	const f32 dAngle = radX > radY ? glm::pi<f32>() / radX : glm::pi<f32>() / radY;

	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		for (f32 angle = 0.f; angle < 2.f * glm::pi<f32>(); angle += dAngle)
		{
			glVertex3f(centerX + radX * cos(angle), centerY + radY * sin(angle), 1.f);
		}
	}
	glEnd();
}

void DebugRenderer::FillEllipse(const FEllipse& ellipse)
{
	FillEllipse(ellipse.Center.x, ellipse.Center.y, ellipse.RadX, ellipse.RadY);
}

void DebugRenderer::FillEllipse(const glm::vec2& center, const f32 radX, const f32 radY)
{
	FillEllipse(center.x, center.y, radX, radY);
}

void DebugRenderer::FillEllipse(const f32 centerX, const f32 centerY, const f32 radX, const f32 radY)
{
	const f32 dAngle = radX > radY ? glm::pi<f32>() / radX : glm::pi<f32>() / radY;

	glBegin(GL_POLYGON);
	{
		for (f32 angle = 0.f; angle < 2.f * glm::pi<f32>(); angle += dAngle)
		{
			glVertex3f(centerX + radX * cos(angle), centerY + radY * sin(angle), 1.f);
		}
	}
	glEnd();
}
#pragma endregion Circles

//ARCS
#pragma region Arcs
void DebugRenderer::DrawArc(const glm::vec2& center, const f32 radX, const f32 radY, const f32 fromAngle, const f32 tillAngle, const f32 lineWidth)
{
	DrawArc(center.x, center.y, radX, radY, fromAngle, tillAngle, lineWidth);
}

void DebugRenderer::DrawArc(const f32 centerX, const f32 centerY, const f32 radX, const f32 radY, const f32 fromAngle, const f32 tillAngle, const f32 lineWidth)
{
	if (fromAngle > tillAngle)
	{
		LOG(Warning, "fromAngle > tillAngle, arc can not be drawn");
		return;
	}

	const f32 dAngle = radX > radY ? glm::pi<f32>() / radX : glm::pi<f32>() / radY;

	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	{
		for (f32 angle = fromAngle; angle < tillAngle; angle += dAngle)
		{
			glVertex3f(centerX + radX * cos(angle), centerY + radY * sin(angle), 1.f);
		}
		glVertex3f(centerX + radX * cos(tillAngle), centerY + radY * sin(tillAngle), 1.f);
	}
	glEnd();
}

void DebugRenderer::FillArc(const glm::vec2& center, const f32 radX, const f32 radY, const f32 fromAngle, const f32 tillAngle)
{
	FillArc(center.x, center.y, radX, radY, fromAngle, tillAngle);
}

void DebugRenderer::FillArc(const f32 centerX, const f32 centerY, const f32 radX, const f32 radY, const f32 fromAngle, const f32 tillAngle)
{
	if (fromAngle > tillAngle)
	{
		LOG(Warning, "fromAngle > tillAngle, arc can not be drawn.");
		return;
	}
	const f32 dAngle = radX > radY ? glm::pi<f32>() / radX : glm::pi<f32>() / radY;

	glBegin(GL_POLYGON);
	{
		glVertex3f(centerX, centerY, 1.f);
		for (f32 angle = fromAngle; angle < tillAngle; angle += dAngle)
		{
			glVertex3f(centerX + radX * cos(angle), centerY + radY * sin(angle), 1.f);
		}
		glVertex3f(centerX + radX * cos(tillAngle), centerY + radY * sin(tillAngle), 1.f);
	}
	glEnd();
}
#pragma endregion Arcs

//POLYGONS
#pragma region Polygons
void DebugRenderer::DrawPolygon(const Polygon2D& vertices, const bool closed, const f32 lineWidth)
{
	glLineWidth(lineWidth);
	closed ? glBegin(GL_LINE_LOOP) : glBegin(GL_LINE_STRIP);
	{
		for (auto [x, y] : vertices)
		{
			glVertex3f(x, y, 1.f);
		}
	}
	glEnd();
}

void DebugRenderer::FillPolygon(const Polygon2D& vertices)
{
	glBegin(GL_POLYGON);
	{
		for (auto [x, y] : vertices)
		{
			glVertex3f(x, y, 1.f);
		}
	}
	glEnd();
}
#pragma endregion Polygons