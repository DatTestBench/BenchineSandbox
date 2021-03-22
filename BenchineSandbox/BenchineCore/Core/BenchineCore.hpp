#pragma once

#include <cstdint>
// General includes
#include <fmt/core.h>
#include <glm/glm.hpp>
struct fuckyou{}; // removing this breaks everything for some reason https://developercommunity.visualstudio.com/t/unexpected-error-c2131-expression-did-not-evaluate/1343697?viewtype=all (yes I could just move the includes, but I can't be bothered)
#include <magic_enum/magic_enum.hpp>

// Type simplification
using u8 	= uint8_t;
using u16 	= uint16_t;
using u32 	= uint32_t;
using u64 	= uint64_t;

using i8 	= int8_t;
using i16 	= int16_t;
using i32 	= int32_t;
using i64	= int64_t;

using f32	= float;
using f64 	= double;

// Debug macros

//todo add compiler specific flags

#if _DEBUG
#define B_DEBUG
#endif 

auto EnumIndex(const auto& e) noexcept
{
	return magic_enum::enum_integer(e);
}

template <typename EnumName>
constexpr auto EnumCount() noexcept
{
	return magic_enum::enum_count<EnumName>();
}
// Adding structured bindings for GLM, do note, this will not work in Clang, nor GCC, for those this should be in namespace glm, not namespace std https://stackoverflow.com/questions/60785190/why-can-i-create-user-defined-structured-bindings-for-glmvec-in-msvc-and-icc
namespace std
{

	template<std::size_t I, auto N, class T, auto Q>
    constexpr auto& get(glm::vec<N, T, Q>& v) noexcept { return v[I]; }
        
	template<std::size_t I, auto N, class T, auto Q>
    constexpr const auto& get(const glm::vec<N, T, Q>& v) noexcept { return v[I]; }
        
	//template< std::size_t I, auto N, class T, auto Q>
	//constexpr auto&& get(glm::vec<N, T, Q>&& v) noexcept { return std::move(v[I]); }
	//
	//template< std::size_t I, auto N, class T, auto Q>
	//constexpr const auto&& get(const glm::vec<N, T, Q>&& v) noexcept { return std::move(v[I]); }
        
	template <auto N, class T, auto Q>
    struct tuple_size<glm::vec<N, T, Q>> : std::integral_constant<std::size_t, N> { };
        
	template <std::size_t I, auto N, class T, auto Q>
    struct tuple_element<I, glm::vec<N, T, Q>> {
		using type = decltype(get<I>(declval<glm::vec<N,T,Q>>()));
	};
};

// Macros
#define DEL_ROF(className) \
className(const className&) = delete; \
className(className&&) noexcept = delete; \
className& operator= (const className&) = delete; \
className& operator= (className&&) noexcept = delete;

#define UNUSED(var) ((void)(var));

// Helper functions

