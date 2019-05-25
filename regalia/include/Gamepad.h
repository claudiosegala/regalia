#pragma once
#include <pch.h>
#include "Vec2.h"

class Gamepad {
public:
	enum Stick {
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
	Vec2 GetStickPosition(Stick side);

private:
	SDL_GameController* controller = nullptr;
	bool buttonState[16] = { false };
	int buttonUpdate[16] = { 0 };
	Sint16 axis[6] = { 0 };
};
