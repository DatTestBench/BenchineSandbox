#pragma once

class BaseComponent;
template<typename Component>
concept IsComponent = std::is_base_of_v<BaseComponent, Component>;

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

class BaseLoader;
template <typename LoaderType>
concept IsResourceLoader = std::is_base_of_v<BaseLoader, LoaderType>;

/*TODO: Add concept for ResourceType*/