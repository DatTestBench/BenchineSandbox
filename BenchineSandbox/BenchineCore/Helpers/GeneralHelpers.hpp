#pragma once
//STL INCLUDES
//************
#include <vector>
#include <string>
//GLM INCLUDES
//************
#include <glm/vec2.hpp>

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

#define ENUM_TO_C_STR(value) std::string(magic_enum::enum_name(value)).c_str()
#define TO_C_STR(value) std::to_string(value).c_str()
#define C_STR_FROM_VIEW(value) std::string(value).c_str()
#define C_STR_FROM_RAW(value) std::string(value).c_str()

//ENUMS
//*****
enum class RenderDepth : u32
{
	//Layer furthest back, use for something like distant landscale, walls, ect
	Background = 1U,
	//Second Layer, use for something like level geometry you want the player to move in front of
	Midgroundlayer1 = 2U,
	//Third layer, use for something like objects that should be in front of level geometry, but behind the player
	Midgroundlayer2 = 3U,
	//Fourth layer, use for stuff like players
	Playerlayer = 4U,
	//Fifth layer, use for foreground objects or level geometry you want to be in front of the player
	Foregroundlayer = 5U
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
	Rect() : Rect(static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0))
	{
	}

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

	#pragma warning (disable : 4201)
	union
	{
		struct
		{
			Type X;
			Type Y;
		};
		glm::vec<2, Type, glm::defaultp> Pos;
	};
	#pragma warning (default : 4201)
	Type Width;
	Type Height;
};

using FRect = Rect<f32>;
using IRect = Rect<i32>;

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
