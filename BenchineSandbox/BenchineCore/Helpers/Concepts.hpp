#pragma once

class BaseComponent;
template<typename Component>
concept IsComponent = std::is_base_of_v<BaseComponent, Component>;