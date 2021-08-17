#pragma once

// STL
#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <string_view> // Reasons for string views https://www.youtube.com/watch?v=fj_CF8xK760
#include <thread>
#include <vector>


#define NANOSVG_IMPLEMENTATION	// Expands implementation


// IMGUI
#pragma warning (push, 0)
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl2.h"
#include "ImGui/imgui_impl_sdl.h"
#pragma warning (pop)
#include "ImNodes/imnodes.h"

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <GL\GLU.h>

#define GLM_FORCE_SILENT_WARNINGS

//Singletons
#include "Core/InputManager.h"
#include "Debugging/Logger.hpp"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Scene/SceneManager.h"

//The Big Helper File
#include "Helpers/GeneralHelpers.hpp"