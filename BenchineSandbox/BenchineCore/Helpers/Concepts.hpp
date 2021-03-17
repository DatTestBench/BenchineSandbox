#pragma once

class BaseComponent;
template<typename Component>
concept IsComponent = std::is_base_of_v<BaseComponent, Component>;

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;