#pragma once
#include <type_traits>

class BaseComponent;
template<typename Component>
concept IsComponent = std::is_base_of_v<BaseComponent, Component>;

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

class BaseLoader;
template <typename LoaderType>
concept IsResourceLoader = std::is_base_of_v<BaseLoader, LoaderType>;

/*TODO: Add concept for ResourceType*/

class BaseGame;
template <class GameInstance>
concept IsGame = std::is_base_of_v<BaseGame, GameInstance>;

class Node;
template <class NodeType>
concept IsNode = std::is_base_of_v<Node, NodeType>;