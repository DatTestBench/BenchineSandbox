#include "BenchinePCH.h"
#include "Core/InputManager.h"
#include <future>
#include <ranges>


#include "BenchineCore.hpp"

bool InputManager::ProcessInput()
{

	ImGuiIO& io = ImGui::GetIO();
	i32 wheel = 0;
	ClearInputs();

	// SDL
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return true;
		}
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			LogKeyPressed(e.key.keysym.scancode);
		}
		if (e.type == SDL_KEYUP)
		{
			LogKeyReleased(e.key.keysym.scancode);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				io.DisplaySize.x = static_cast<f32>(e.window.data1);
				io.DisplaySize.y = static_cast<f32>(e.window.data2);
			}
		}
		if (e.type == SDL_MOUSEWHEEL)
		{
			wheel = e.wheel.y;
		}
	}

	// XINPUT https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput
	DWORD dwResult{};

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Get the state of the controller
		dwResult = XInputGetState(i, &state); // TODO: This thing is awfully slow, find a way to not have to recheck it every frame;
		if (dwResult == ERROR_SUCCESS && !m_Controllers.at(i).IsConnected)
		{
			// Controller Connected
			m_Controllers.at(i).IsConnected = true;
			LOG(Debug, "Controller Connected");
		}
		else if (dwResult != ERROR_SUCCESS && m_Controllers[i].IsConnected)
		{
			// Controller Disconnected
			m_Controllers.at(i).IsConnected = false;
			LOG(Debug, "Controller Disconnected");
		}
		// Bind all inputs to each controller
		CheckControllerInput(i, state, GamepadButton::DPAD_UP, XINPUT_GAMEPAD_DPAD_UP);
		CheckControllerInput(i, state, GamepadButton::DPAD_DOWN, XINPUT_GAMEPAD_DPAD_DOWN);
		CheckControllerInput(i, state, GamepadButton::DPAD_LEFT, XINPUT_GAMEPAD_DPAD_LEFT);
		CheckControllerInput(i, state, GamepadButton::DPAD_RIGHT, XINPUT_GAMEPAD_DPAD_RIGHT);
		CheckControllerInput(i, state, GamepadButton::START, XINPUT_GAMEPAD_START);
		CheckControllerInput(i, state, GamepadButton::BACK, XINPUT_GAMEPAD_BACK);
		CheckControllerInput(i, state, GamepadButton::LEFT_THUMB, XINPUT_GAMEPAD_LEFT_THUMB);
		CheckControllerInput(i, state, GamepadButton::RIGHT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB);
		CheckControllerInput(i, state, GamepadButton::LEFT_SHOULDER, XINPUT_GAMEPAD_LEFT_SHOULDER);
		CheckControllerInput(i, state, GamepadButton::RIGHT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER);
		CheckControllerInput(i, state, GamepadButton::A, XINPUT_GAMEPAD_A);
		CheckControllerInput(i, state, GamepadButton::B, XINPUT_GAMEPAD_B);
		CheckControllerInput(i, state, GamepadButton::X, XINPUT_GAMEPAD_X);
		CheckControllerInput(i, state, GamepadButton::Y, XINPUT_GAMEPAD_Y);

	}

	i32 mouseX, mouseY;
	const auto buttons = SDL_GetMouseState(&mouseX, &mouseY);

	io.MousePos = ImVec2(static_cast<f32>(mouseX), static_cast<f32>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<f32>(wheel);



	//for (auto bind : m_InputBinds | std::views::values)
	for (auto& [actionId, callback, state, keyCode, mouseCode, button, controller, isActive] : m_InputBinds | std::views::values)
	{
		// Keyboard Checks
		bool keyBoardActive = false;

		if (state == InputState::Down)
		{
			const u8* keyboardState = SDL_GetKeyboardState(nullptr);
			if (keyboardState[keyCode])
			{
				//auto a = std::async(bind.second.CallBack);
				callback();
				keyBoardActive = true;
			}
		}
		else
		{
			for (auto& keyEvent : m_KeyEvents)
			{
				if (keyEvent.KeyCode == keyCode && keyEvent.State == state)
				{
					//auto a = std::async(bind.second.CallBack);
					callback();
					keyBoardActive = true;
					keyEvent.Processed = true;
				}
			}
		}

		// XINPUT Checks
		bool controllerActive = false;
		if (button != GamepadButton::NONE)
		{
			if (m_Controllers.at(EnumIndex(controller)).Buttons.at(EnumIndex(button)) 
				&& (m_Controllers.at(EnumIndex(controller)).ButtonStates.at(EnumIndex(button)) == state))
			{
				//auto a = std::async(bind.second.CallBack);
				callback();
				controllerActive = true;
			}
		}
		isActive = keyBoardActive || controllerActive;
	}

	return false;
}

bool InputManager::AddInputBinding(InputBinding binding)
{
	const size_t oldSize = m_InputBinds.size();
	m_InputBinds.emplace(binding.ActionId, binding);
	const size_t newSize = m_InputBinds.size();

	if (oldSize == newSize)
	{
		LOG(Warning, "Input with ID {0} already exists", binding.ActionId);
		return false;
	}
	return true;
}

bool InputManager::IsBindingActive(std::string_view)
{
	return true;
	//return m_InputBinds.at(actionId).IsActive;
}

bool InputManager::IsPressed(GamepadButton button, const u32 controllerId)
{

	if (m_Controllers.at(controllerId).IsConnected)
	{
		return m_Controllers.at(controllerId).Buttons.at(EnumIndex(button));
	}
	return false;
}

void InputManager::LogKeyPressed(const SDL_Scancode key)
{
	m_KeyEvents.emplace_back(KeyEvent(key, InputState::Pressed));
}
void InputManager::LogKeyReleased(const SDL_Scancode key)
{
	m_KeyEvents.emplace_back(KeyEvent(key, InputState::Released));
}


MouseState InputManager::GetMouseState()
{
	i32 x, y;
	const u32 mouseState = SDL_GetMouseState(&x, &y);
	return MouseState(x, y, mouseState);
}

void InputManager::ClearInputs()
{
	m_KeyEvents.erase(std::ranges::remove_if(m_KeyEvents, [](const KeyEvent& keyEvent) { return keyEvent.Processed; }).begin(), m_KeyEvents.end());
}

void InputManager::CheckControllerInput(const DWORD index, const XINPUT_STATE xInputState, const GamepadButton button, const i32 xInputConstant)
{
	const bool previous = m_Controllers.at(index).Buttons.at(EnumIndex(button));
	if (xInputState.Gamepad.wButtons & xInputConstant)
	{
		m_Controllers.at(index).Buttons.at(EnumIndex(button)) = true;
		m_Controllers.at(index).ButtonStates.at(EnumIndex(button)) = previous ? InputState::Down : InputState::Pressed;
	}
	else
	{
		m_Controllers.at(index).Buttons.at(EnumIndex(button)) = false;
	}
}