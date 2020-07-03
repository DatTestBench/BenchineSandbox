#pragma once
//STL INCLUDES
//************
#include <vector>
#include <numeric>
#include <string>
#include <fstream>
#include <filesystem>
//GLM INCLUDES
//************
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <glm/mat3x2.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

//MISC INCLUDES
//*************
#include "Helpers/json.hpp"
//USINGS
//******
using Collider2D = std::vector<glm::vec2>;
using Polygon2D = std::vector<glm::vec2>;
using VertexUV = std::pair<glm::vec2, glm::vec2>;
using json = nlohmann::json;

//DEFINES
//*******
#define INPUT InputManager::GetInstance()
#define RESOURCES ResourceManager::GetInstance()
#define RENDERER Renderer::GetInstance()

//MACROS
//******
#ifdef _DEBUG
#define DEBUGONLY(x) x
#else
#define DEBUGONLY(x) do{}while(0)
#endif

//ENUMS
//*****
enum class RenderDepth : uint32_t
{
	//Layer furthest back, use for something like distant landscale, walls, ect
	BACKGROUND = 1U,
	//Second Layer, use for something like level geometry you want the player to move in front of
	MIDGROUNDLAYER1 = 2U,
	//Third layer, use for something like objects that should be in front of level geometry, but behind the player
	MIDGROUNDLAYER2 = 3U,
	//Fourth layer, use for stuff like players
	PLAYERLAYER = 4U,
	//Fifth layer, use for foreground objects or level geometry you want to be in front of the player
	FOREGROUNDLAYER = 5U
};

//HELPER STRUCTS
//**************
struct Projection2D
{
	explicit Projection2D(float val)
		: Min(val)
		, Max(val)
	{}
	explicit Projection2D(float min, float max)
		: Min(min)
		, Max(max)
	{}
	float Min;
	float Max;
};


struct WindowSettings
{
	explicit WindowSettings(const std::string& name = "Window", uint32_t width = 1600U, uint32_t height = 960U, bool enableVSync = true)
		: Name(name)
		, Width(width)
		, Height(height)
		, EnableVSync(enableVSync)
	{}
	std::string Name;
	uint32_t Width;
	uint32_t Height;
	bool EnableVSync;
};

struct FRect
{
	FRect() : FRect(0.f, 0.f, 0.f, 0.f) {}
	explicit FRect(float x, float y, float width, float height)
		: Pos(x, y)
		, Width(width)
		, Height(height)
	{}
	explicit FRect(glm::vec2 pos, float width, float height)
		: Pos(pos)
		, Width(width)
		, Height(height)
	{}

	glm::vec2 Pos;
	float Width;
	float Height;
};

struct IRect
{
	IRect() : IRect(0, 0, 0, 0) {}
	explicit IRect(int32_t x, int32_t y, uint32_t width, uint32_t height)
		: Pos(x, y)
		, Width(width)
		, Height(height)
	{}
	explicit IRect(glm::ivec2 pos, uint32_t width, uint32_t height)
		: Pos(pos)
		, Width(width)
		, Height(height)
	{}

	glm::ivec2 Pos;
	uint32_t Width;
	uint32_t Height;
};

struct FEllipse
{
	explicit FEllipse(const glm::vec2& center, float radX, float radY)
		: Center(center)
		, RadX(radX)
		, RadY(radY)
	{}

	glm::vec2 Center;
	float RadX;
	float RadY;
};


struct DropSettings
{
	explicit DropSettings(const std::string& dropFile, const std::string& dropName, const glm::vec2& pos, const glm::vec2& scale)
		: DropFile(dropFile)
		, DropName(dropName)
		, Pos(pos)
		, Scale(scale)
	{}

	std::string DropFile;
	std::string DropName;
	glm::vec2 Pos;
	glm::vec2 Scale;
};

//MATH HELPERS
//************
namespace MathHelper
{
	[[nodiscard]] auto PolyCenter(const Polygon2D& polygon) noexcept-> const glm::vec2;
}

//COLLISION HELPERS
//*****************
namespace CollisionHelper
{
	[[nodiscard]] constexpr auto IsPointInFRect(const glm::vec2& p, const FRect& r) noexcept-> bool;
}

//JSON HELPER
//***********
namespace JsonHelper
{
	[[nodiscard]] auto ReadJson(const std::string& filePath) noexcept-> json;
	void WriteJson(const json& j, const std::string& filePath) noexcept;
}

//SVG HELPER
namespace SvgHelper
{
	[[nodiscard]] auto ReadSvg(const std::string& filePath) noexcept-> std::vector<Polygon2D>;
}