#pragma once
// TODO: Prime candidate for modules

#include <string>
#include <vector>
#include "Core/CoreBasicTypes.hpp"
#include "Helpers/Concepts.hpp"
#include "glm/glm.hpp"

using Collider2D = std::vector<glm::vec2>;
using Polygon2D = std::vector<glm::vec2>;
using VertexUV = std::pair<glm::vec2, glm::vec2>;

struct Projection2D
{
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
	Rect() = default;

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

	[[nodiscard]] bool Contains(const glm::vec2& point) const noexcept
	{
		return point.x >= Pos.x
		&& point.x <= Pos.x + Width
		&& point.y >= Pos.y
		&& point.y <= Pos.y + Height;
	}
	
	glm::vec<2, Type, glm::defaultp> Pos = {};
	Type Width = {};
	Type Height = {};
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

// Adding structured bindings for GLM, do note, this will not work in Clang, nor GCC, for those this should be in namespace glm, not namespace std https://stackoverflow.com/questions/60785190/why-can-i-create-user-defined-structured-bindings-for-glmvec-in-msvc-and-icc
namespace std
{
	template <std::size_t I, auto N, class T, auto Q>
	constexpr auto& get(glm::vec<N, T, Q>& v) noexcept { return v[I]; }

	template <std::size_t I, auto N, class T, auto Q>
	constexpr const auto& get(const glm::vec<N, T, Q>& v) noexcept { return v[I]; }

	//template< std::size_t I, auto N, class T, auto Q>
	//constexpr auto&& get(glm::vec<N, T, Q>&& v) noexcept { return std::move(v[I]); }
	//
	//template< std::size_t I, auto N, class T, auto Q>
	//constexpr const auto&& get(const glm::vec<N, T, Q>&& v) noexcept { return std::move(v[I]); }

	template <auto N, class T, auto Q>
	struct tuple_size<glm::vec<N, T, Q>> : std::integral_constant<std::size_t, N>
	{
	};

	template <std::size_t I, auto N, class T, auto Q>
	struct tuple_element<I, glm::vec<N, T, Q>>
	{
		using type = decltype(get<I>(declval<glm::vec<N, T, Q>>()));
	};
}
