#include <pch.h>
#include <Constants.h>
#include <InputManager.h>
#include <Game.h>

// TODO: q gambiarra é essa
#define PROTECT_RANGE(number, defaultValue)     \
	if (unsigned(number) >= controllers.size()) \
	return (defaultValue)

InputManager& InputManager::GetInstance() {
	static InputManager instance;

	return instance;
}

InputManager::InputManager() {
	LoadControllers();
}

void InputManager::Update() {
	Setup();
	RetrieveMouse();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		TreatEvent(event);
	}
}

bool InputManager::KeyPress(int key) {
	return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key) {
	return !keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key) {
	return keyState[key];
}

bool InputManager::MousePress(int button) {
	return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button) {
	return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button) {
	return mouseState[button];
}

Vec2 InputManager::GetMouse(Vec2 relative) const {
	return {
		float(GetMouseX()) + relative.x,
		float(GetMouseY()) + relative.y
	};
}

int InputManager::GetMouseX() const {
	return mouseX;
}

int InputManager::GetMouseY() const {
	return mouseY;
}

bool InputManager::GamepadPress(SDL_GameControllerButton button) {
	for (auto i = 0; i < (int)controllers.size(); i++) {
		if (GamepadPress(button, i)) {
			return true;
		}
	}
	return false;
}

bool InputManager::GamepadPress(SDL_GameControllerButton button, int controllerNumber) {
	PROTECT_RANGE(controllerNumber, false);
	return controllers[controllerNumber].ButtonPressed(button, updateCounter);
}

bool InputManager::GamepadRelease(SDL_GameControllerButton button) {
	for (auto i = 0; i < (int)controllers.size(); i++) {
		if (GamepadRelease(button, i)) {
			return true;
		}
	}
	return false;
}

bool InputManager::GamepadRelease(SDL_GameControllerButton button, int controllerNumber) {
	PROTECT_RANGE(controllerNumber, false);
	return controllers[controllerNumber].ButtonReleased(button, updateCounter);
}

bool InputManager::IsGamepadDown(SDL_GameControllerButton button) {
	for (auto i = 0; i < (int)controllers.size(); i++) {
		if (IsGamepadDown(button, i)) {
			return true;
		}
	}
	return false;
}

bool InputManager::IsGamepadDown(SDL_GameControllerButton button, int controllerNumber) {
	PROTECT_RANGE(controllerNumber, false);
	return controllers[controllerNumber].IsButtonDown(button);
}

Vec2 InputManager::GamepadLeftStick(int controllerNumber) {
	PROTECT_RANGE(controllerNumber, Vec2());
	return controllers[controllerNumber].GetStickPosition(Gamepad::Left);
}

Vec2 InputManager::GamepadRightStick(int controllerNumber) {
	PROTECT_RANGE(controllerNumber, Vec2());
	return controllers[controllerNumber].GetStickPosition(Gamepad::Right);
}

bool InputManager::PopRequested() {
	return KeyPress(Constants::Key::Escape);
}

bool InputManager::QuitRequested() const {
	return quitRequested;
}

void InputManager::Setup() {
	quitRequested = false;
	updateCounter++;
}

void InputManager::RetrieveMouse() {
	SDL_GetMouseState(&mouseX, &mouseY);
}

void InputManager::TreatEvent(SDL_Event& event) {
	switch (event.type) {
	// Gamepad events
	case SDL_CONTROLLERAXISMOTION:
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP: {
		controllers[event.cbutton.which].Update(event, updateCounter);
		break;
	}
	case SDL_QUIT: {
		quitRequested = true;
		break;
	}
	case SDL_KEYDOWN: {
		auto isRepeated = event.key.repeat == 1;

		if (!isRepeated) {
			auto key = event.key.keysym.sym;

			keyState[key] = true;
			keyUpdate[key] = updateCounter;
		}
		break;
	}
	case SDL_KEYUP: {
		auto isRepeated = event.key.repeat == 1;

		if (!isRepeated) {
			auto key = event.key.keysym.sym;

			keyState[key] = false;
			keyUpdate[key] = updateCounter;
		}
		break;
	}
	case SDL_MOUSEBUTTONDOWN: {
		auto idx = event.button.button;
		mouseState[idx] = true;
		mouseUpdate[idx] = updateCounter;
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		auto idx = event.button.button;
		mouseState[idx] = false;
		mouseUpdate[idx] = updateCounter;
		break;
	}
	default:
		break;
	}
}

void InputManager::LoadControllers() {
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controllers.emplace_back(i);
		}
	}
}