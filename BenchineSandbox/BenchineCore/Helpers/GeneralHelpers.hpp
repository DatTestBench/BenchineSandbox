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
#include <glm/vec2.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

//MISC INCLUDES
//*************
#include "json/json.hpp"
#include "Helpers/Concepts.hpp"
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
// todo unfuck this
#ifdef _DEBUG
#define DEBUGONLY(x) x
#else
#define DEBUGONLY(x) do{}while(0)
#endif

#define ENUM_TO_C_STR(value) std::string(magic_enum::enum_name(value)).c_str()
#define TO_C_STR(value) std::to_string(value).c_str()
#define C_STR_FROM_VIEW(value) std::string(value).c_str()
#define C_STR_FROM_RAW(value) std::string(value).c_str()

//ENUMS
//*****
enum class RenderDepth : u32
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
	explicit Projection2D(const f32 val)
		: Min(val)
		, Max(val)
	{
	}
	explicit Projection2D(const f32 min, const f32 max)
		: Min(min)
		, Max(max)
	{
	}
	f32 Min;
	f32 Max;
};


struct WindowSettings
{
	explicit WindowSettings(const std::string& name = "Window", const u32 width = 1600U, const u32 height = 960U, const bool enableVSync = true)
		: Name(name)
		, Width(width)
		, Height(height)
		, EnableVSync(enableVSync)
	{
	}
	std::string Name;
	u32 Width;
	u32 Height;
	bool EnableVSync;
};

template <Numeric Type>
struct Rect
{
	Rect() : Rect(static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0)) {}
	
	explicit Rect(const Type x, const Type y, const Type width, const Type height)
		: Pos(x, y)
		, Width(width)
		, Height(height)
	{
	}

	explicit Rect(const glm::vec<2, Type, glm::defaultp> pos, const Type width, const Type height)
		: Pos(pos)
		, Width(width)
		, Height(height)
	{
	}

	[[nodiscard]] auto Contains(const glm::vec2& point) const -> bool
	{
		return point.x >= Pos.x
               && point.x <= Pos.x + Width
               && point.y >= Pos.y
               && point.y <= Pos.y + Height;
	}
	
	glm::vec<2, Type, glm::defaultp> Pos;
	Type Width;
	Type Height;
};

using FRect = Rect<f32>;
using IRect = Rect<i32>;
/*struct FRect
{
	FRect() : FRect(0.f, 0.f, 0.f, 0.f)
	{
	}
	explicit FRect(const f32 x, const f32 y, const f32 width, const f32 height)
		: Pos(x, y)
		, Width(width)
		, Height(height)
	{
	}
	explicit FRect(const glm::vec2& pos, const f32 width, const f32 height)
		: Pos(pos)
		, Width(width)
		, Height(height)
	{
	}



	glm::vec2 Pos;
	f32 Width;
	f32 Height;
};

struct IRect
{
	IRect() : IRect(0, 0, 0, 0)
	{
	}
	explicit IRect(const u32 x, const u32 y, const u32 width, const u32 height)
		: Pos(x, y)
		, Width(width)
		, Height(height)
	{
	}
	explicit IRect(const glm::ivec2& pos, const u32 width, const u32 height)
		: Pos(pos)
		, Width(width)
		, Height(height)
	{
	}

	[[nodiscard]] auto Contains(const glm::vec2& point) const -> bool
	{
		return point.x >= Pos.x
			   && point.x <= Pos.x + Width
			   && point.y >= Pos.y
			   && point.y <= Pos.y + Height;
	}

	glm::ivec2 Pos;
	u32 Width;
	u32 Height;
};*/

struct FEllipse
{
	explicit FEllipse(const glm::vec2& center, const f32 radX, const f32 radY)
		: Center(center)
		, RadX(radX)
		, RadY(radY)
	{
	}

	glm::vec2 Center;
	f32 RadX;
	f32 RadY;
};

struct DropSettings
{
	explicit DropSettings(const std::string& dropFile, const std::string& dropName, const glm::vec2& pos, const glm::vec2& scale)
		: DropFile(dropFile)
		, DropName(dropName)
		, Pos(pos)
		, Scale(scale)
	{
	}

	std::string DropFile;
	std::string DropName;
	glm::vec2 Pos;
	glm::vec2 Scale;
};

//MATH HELPERS
//************
namespace MathHelper
{
	[[nodiscard]] auto PolyCenter(const Polygon2D& polygon) noexcept -> glm::vec2;
}

//COLLISION HELPERS
//*****************
namespace CollisionHelper
{
	[[nodiscard]] constexpr auto IsPointInFRect(const glm::vec2& p, const FRect& r) noexcept -> bool;
}

//JSON HELPER
//***********
namespace JsonHelper
{
	[[nodiscard]] auto ReadJson(const std::string& filePath) noexcept -> json;
	void WriteJson(const json& j, const std::string& filePath) noexcept;
}

//SVG HELPER
namespace SvgHelper
{
	[[nodiscard]] auto ReadSvg(const std::string& filePath) noexcept -> std::vector<Polygon2D>;
}
