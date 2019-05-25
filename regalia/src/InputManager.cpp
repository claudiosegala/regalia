#include <pch.h>
#include <Constants.h>
#include <InputManager.h>

#define PROTECT_RANGE(number, defaultValue)       \
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

void InputManager::Setup() {
	this->quitRequested = false;
	this->updateCounter++;
}

void InputManager::RetrieveMouse() {
	SDL_GetMouseState(&this->mouseX, &this->mouseY);
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
		this->quitRequested = true;
		break;
	}
	case SDL_KEYDOWN: {
		auto isRepeated = event.key.repeat == 1;

		if (!isRepeated) {
			auto key = event.key.keysym.sym;

			this->keyState[key] = true;
			this->keyUpdate[key] = this->updateCounter;
		}
		break;
	}
	case SDL_KEYUP: {
		auto isRepeated = event.key.repeat == 1;

		if (!isRepeated) {
			auto key = event.key.keysym.sym;

			this->keyState[key] = false;
			this->keyUpdate[key] = this->updateCounter;
		}
		break;
	}
	case SDL_MOUSEBUTTONDOWN: {
		auto idx = event.button.button;
		this->mouseState[idx] = true;
		this->mouseUpdate[idx] = this->updateCounter;
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		auto idx = event.button.button;
		this->mouseState[idx] = false;
		this->mouseUpdate[idx] = this->updateCounter;
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

Vec2 InputManager::GetMouse(Vec2 relative) {
	return Vec2 {
		static_cast<float>(GetMouseX()) + relative.x,
		static_cast<float>(GetMouseY()) + relative.y
	};
}

int InputManager::GetMouseX() const {
	return mouseX;
}

int InputManager::GetMouseY() const {
	return mouseY;
}

bool InputManager::GamepadPress(SDL_GameControllerButton button) {
	for (size_t i = 0; i < controllers.size(); i++) {
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
	for (size_t i = 0; i < controllers.size(); i++) {
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
	for (size_t i = 0; i < controllers.size(); i++) {
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

bool InputManager::IsPopRequested() {
	return GetInstance().KeyPress(Constants::Key::Escape);
}

bool InputManager::QuitRequested() {
	return this->quitRequested;
}

bool InputManager::IsQuitRequested() {
	return GetInstance().QuitRequested();
}
