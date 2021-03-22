#pragma once
#include <XInput.h>
#include <bitset>
#include <map>
#include <vector>
#include <functional>

#include "BenchineCore.hpp"
#include "Helpers/Singleton.hpp"

enum class InputState
{
	Pressed,
	Released,
	Down
};

enum class GamepadButton : u16
{
	DPAD_UP,
	DPAD_DOWN,
	DPAD_LEFT,
	DPAD_RIGHT,
	START,
	BACK,
	LEFT_THUMB,
	RIGHT_THUMB,
	LEFT_SHOULDER,
	RIGHT_SHOULDER,
	A,
	B,
	X,
	Y,
	NONE
};
struct InputBinding
{
	std::string_view ActionId;
	std::function<void()> CallBack;
	InputState State;
	i32 KeyCode; // Remapped to an SDL keycode
	i32 MouseCode;
	GamepadButton Button;
	i32 ControllerId;
	bool IsActive;

	explicit InputBinding(const std::string_view id, const std::function<void()> callBack, const InputState state, const i32 keyCode = -1, const i32 mouseCode = -1, const GamepadButton button = GamepadButton::NONE, const i32 controllerId = 0)
		: ActionId(id)
		, CallBack(callBack)
		, State(state)
		, KeyCode(SDL_GetScancodeFromKey(keyCode))
		, MouseCode(mouseCode)
		, Button(button)
		, ControllerId(controllerId)
		, IsActive(false)
	{
	}
};

struct KeyEvent
{
	i32 KeyCode;
	InputState State;
	bool Processed;
	KeyEvent(const i32 keyCode, const InputState state)
		: KeyCode(keyCode)
		, State(state)
		, Processed(false)
	{
	}
};

struct Controller
{
	bool IsConnected;
	std::array<bool, magic_enum::enum_count<GamepadButton>()> Buttons;
	std::array<InputState, magic_enum::enum_count<GamepadButton>()> ButtonStates;
};

struct MouseState
{
	i32 x;
	i32 y;
	u32 state;
};

class InputManager final : public Singleton<InputManager>
{
public:
	explicit InputManager(Token)
		: m_Controllers()
	{
	}

	bool AddInputBinding(InputBinding binding);
	bool IsBindingActive(std::string_view actionId);

	bool ProcessInput();
	bool IsPressed(GamepadButton button, uint32_t controllerId);
	static MouseState GetMouseState();


private:

	void LogKeyPressed(SDL_Scancode key);
	void LogKeyReleased(SDL_Scancode key);
	std::vector<KeyEvent> m_KeyEvents;

	std::array<Controller, XUSER_MAX_COUNT> m_Controllers;

	std::multimap<std::string_view, InputBinding> m_InputBinds;

	void ClearInputs();
	void CheckControllerInput(DWORD index, XINPUT_STATE xInputState, GamepadButton button, i32 xInputConstant);
};
