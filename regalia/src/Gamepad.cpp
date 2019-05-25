#include "pch.h"
#include "Gamepad.h"
#include "Constants.h"

Gamepad::Gamepad(int index)
    : controller(SDL_GameControllerOpen(index)) {
}

void Gamepad::Update(const SDL_Event& event, int counter) {
	switch (event.type) {
	case SDL_CONTROLLERBUTTONUP:
		buttonState[event.cbutton.button] = false;
		buttonUpdate[event.cbutton.button] = counter;
		break;
	case SDL_CONTROLLERBUTTONDOWN:
		buttonState[event.cbutton.button] = true;
		buttonUpdate[event.cbutton.button] = counter;
		break;
	case SDL_CONTROLLERAXISMOTION:
		axis[event.caxis.axis] = event.caxis.value;
		break;
	default:
		break;
	}
}

bool Gamepad::IsButtonDown(SDL_GameControllerButton button) {
	return buttonState[button];
}

bool Gamepad::ButtonPressed(SDL_GameControllerButton button, int counter) {
	return buttonState[button] && buttonUpdate[button] == counter;
}

bool Gamepad::ButtonReleased(SDL_GameControllerButton button, int counter) {
	return !buttonState[button] && buttonUpdate[button] == counter;
}

Vec2 Gamepad::GetStickPosition(Stick side) {
	auto position = side == Left
	    ? Vec2(float(axis[SDL_CONTROLLER_AXIS_LEFTX]), float(axis[SDL_CONTROLLER_AXIS_LEFTY]))
	    : Vec2(float(axis[SDL_CONTROLLER_AXIS_RIGHTX]), float(axis[SDL_CONTROLLER_AXIS_RIGHTY]));
	if (abs(position.x) < Constants::Gamepad::StickDeadZone) {
		position.x = 0.f;
	}
	if (abs(position.y) < Constants::Gamepad::StickDeadZone) {
		position.y = 0.f;
	}
	return position / 32768.f;
}
