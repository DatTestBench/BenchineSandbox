#pragma once
#include <XInput.h>
#include <bitset>
#include <map>
#include <tuple>
#include <vector>
#include <functional>
#include <string_view>
#include <functional>
#include "Helpers/Singleton.h"

enum InputState
{
	Pressed,
	Released,
	Down
};

enum GamepadButton : uint16_t
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
	MAX_BUTTONS
};
struct InputBinding
{
	std::string_view ActionId;
	std::function<void()> CallBack;
	InputState State;
	int KeyCode; // Remapped to an SDL keycode
	int MouseCode;
	GamepadButton Button;
	int ControllerId;
	bool IsActive;

	explicit InputBinding(std::string_view id, std::function<void()> callBack, InputState state, int keyCode = -1, int mouseCode = -1, GamepadButton button = MAX_BUTTONS, int controllerId = 0)
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
	int KeyCode;
	InputState State;
	bool Processed;
	KeyEvent(int keyCode, InputState state)
		: KeyCode(keyCode)
		, State(state)
		, Processed(false)
	{

	}
};

struct Controller
{
	bool IsConnected;
	std::array<bool, MAX_BUTTONS> Buttons;
	std::array<InputState, MAX_BUTTONS> ButtonStates;
};

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager(token)
		: m_KeyEvents()
		, m_Controllers()
		, m_InputBinds()
	{

	}

	bool AddInputBinding(InputBinding binding);
	bool IsBindingActive(std::string_view actionId);

	bool ProcessInput();
	bool IsPressed(GamepadButton button, int controllerId);
	std::tuple<int, int, Uint32> GetMouseState();


private:

	void LogKeyPressed(SDL_Scancode key);
	void LogKeyReleased(SDL_Scancode key);
	std::vector<KeyEvent> m_KeyEvents;

	std::array<Controller, XUSER_MAX_COUNT> m_Controllers;
	
	std::multimap<std::string_view, InputBinding> m_InputBinds;

	void ClearInputs();
	void CheckControllerInput(DWORD index, XINPUT_STATE xInputState, GamepadButton Button, int xInputConstant);
};


