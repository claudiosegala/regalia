#pragma once
#include <pch.h>
#include <Vec2.h>

class Gamepad {
public:
	enum class Stick {
		Left,
		Right
	};

	enum class Trigger {
		Left,
		Right
	};

	Gamepad(int index);
	
	Gamepad(const Gamepad& other) = delete;
	
	Gamepad(Gamepad&& other) = default;
	
	void Update(const SDL_Event& event, int counter);
	
	bool IsButtonDown(SDL_GameControllerButton button);
	
	bool ButtonPressed(SDL_GameControllerButton button, int counter);
	
	bool ButtonReleased(SDL_GameControllerButton button, int counter);

	bool IsAxisHolded(SDL_GameControllerAxis axis);

	bool AxisBinded(SDL_GameControllerAxis axis, int counter);

	bool AxisReleased(SDL_GameControllerAxis axis, int counter);

	void Rumble(float intensity, unsigned int duration);
	
	Vec2 GetStickPosition(Stick side);

	int GetTriggerIntensity(Trigger side);

private:
	SDL_GameController* controller = nullptr;

	SDL_Haptic* haptic = nullptr;
	
	bool buttonState[16] = { false };
	
	int buttonUpdate[16] = { 0 };
	
	Sint16 axisState[6] = { 0 };

	int axisUpdate[6] = { 0 };
};
