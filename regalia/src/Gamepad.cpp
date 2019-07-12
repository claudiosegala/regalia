#include <pch.h>
#include <Gamepad.h>
#include <Constants.h>

Gamepad::Gamepad(int index)
    : controller(SDL_GameControllerOpen(index))
    , haptic(SDL_HapticOpen(index)) {
	if (haptic) {
		SDL_HapticRumbleInit(haptic);
	}
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
			axisState[event.caxis.axis] = event.caxis.value;
			axisUpdate[event.caxis.axis] = counter;
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

bool Gamepad::IsAxisHolded(SDL_GameControllerAxis axis) {
	return axisState[axis] > Constants::Gamepad::TriggerDeadZone;
}

bool Gamepad::AxisBinded(SDL_GameControllerAxis axis, int counter) {
	return axisState[axis] > Constants::Gamepad::TriggerDeadZone && axisUpdate[axis] == counter;
}

bool Gamepad::AxisReleased(SDL_GameControllerAxis axis, int counter) {
	return axisState[axis] <= Constants::Gamepad::TriggerDeadZone && axisUpdate[axis] == counter;
}

void Gamepad::Rumble(float intensity, unsigned int duration) {
	SDL_HapticRumblePlay(haptic, intensity, duration);
}

Vec2 Gamepad::GetStickPosition(Stick side) {
	auto position = side == Stick::Left
	    ? Vec2(float(axisState[SDL_CONTROLLER_AXIS_LEFTX]), float(axisState[SDL_CONTROLLER_AXIS_LEFTY]))
	    : Vec2(float(axisState[SDL_CONTROLLER_AXIS_RIGHTX]), float(axisState[SDL_CONTROLLER_AXIS_RIGHTY]));
	if (abs(position.x) < Constants::Gamepad::StickDeadZone) {
		position.x = 0.f;
	}
	if (abs(position.y) < Constants::Gamepad::StickDeadZone) {
		position.y = 0.f;
	}
	return position / 32768.f;
}

int Gamepad::GetTriggerIntensity(Trigger side) {
	return side == Trigger::Left ? axisState[SDL_CONTROLLER_AXIS_TRIGGERLEFT]: axisState[SDL_CONTROLLER_AXIS_TRIGGERRIGHT];
}
