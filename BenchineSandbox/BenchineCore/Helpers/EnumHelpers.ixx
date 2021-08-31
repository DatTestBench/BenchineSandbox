module;
#include "magic_enum/magic_enum.hpp"

export module EnumHelpers;

export auto EnumIndex(const auto& e) noexcept
{
	return magic_enum::enum_index(e).value();
}

export template <typename EnumName>
constexpr auto EnumCount() noexcept
{
	return magic_enum::enum_count<EnumName>();
}
