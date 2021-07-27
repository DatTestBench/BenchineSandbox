#pragma once

// STL
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <map>
#include <list>
#include <functional>
#include <chrono>
#include <thread>
#include <algorithm>
#include <array>
#include <string>
#include <string_view> // Reasons for string views https://www.youtube.com/watch?v=fj_CF8xK760

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// IMGUI
#pragma warning (push, 0)
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl2.h"
#pragma warning (pop)

// SDL
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

//Singletons
#include "Resources/ResourceManager.h"
#include "Core/InputManager.h"
#include "Scene/SceneManager.h"
#include "Debugging/Logger.hpp"
#include "Graphics/Renderer.h"

//The Big Helper File
#include "Helpers/GeneralHelpers.hpp"