#include <pch.h>
#include <Constants.h>
#include <Logger.h>
#include <InputManager.h>
#include "Game.h"


InputManager& InputManager::GetInstance() {
	static InputManager instance;

	return instance;
}

InputManager::InputManager()
    : mouseState { 0, 0, 0, 0, 0, 0 }
    , mouseUpdate { 0, 0, 0, 0, 0, 0 } {
	this->quitRequested = false;
	this->updateCounter = 0;
	this->mouseX = 0;
	this->mouseY = 0;
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
	case SDL_JOYDEVICEREMOVED: {
		Logger::Error("Joystick Removed!");
		this->quitRequested = true;
		break;
	}
	case SDL_JOYAXISMOTION:
		printf("Joystick %d axis %d value: %d\n", event.jaxis.which, event.jaxis.axis, event.jaxis.value);
		break;
	case SDL_JOYHATMOTION:
		printf("Joystick %d hat %d value:", event.jhat.which, event.jhat.hat);
		if (event.jhat.value == SDL_HAT_CENTERED)
			printf(" centered");
		if (event.jhat.value & SDL_HAT_UP)
			printf(" up");
		if (event.jhat.value & SDL_HAT_RIGHT)
			printf(" right");
		if (event.jhat.value & SDL_HAT_DOWN)
			printf(" down");
		if (event.jhat.value & SDL_HAT_LEFT)
			printf(" left");
		printf("\n");
		break;
	case SDL_JOYBALLMOTION:
		printf("Joystick %d ball %d delta: (%d,%d)\n", event.jball.which, event.jball.ball, event.jball.xrel, event.jball.yrel);
		break;
	case SDL_JOYBUTTONDOWN:
		printf("Joystick %d button %d down\n",  event.jbutton.which, event.jbutton.button);
		break;
	case SDL_JOYBUTTONUP:
		printf("Joystick %d button %d up\n",  event.jbutton.which, event.jbutton.button);
		break;
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
	case SDL_WINDOWEVENT_SIZE_CHANGED: {
		std::cout << "Window resize" << std::endl;
		// Set the dynamic window scale
		auto game = Game::GetInstance();
		int windowWidth, windowHeight;
		SDL_GetWindowSize(game->GetWindow(), &windowWidth, &windowHeight);
		SDL_RenderSetScale(game->GetRenderer(), float(windowWidth) / Constants::Window::Width, float(windowHeight) / Constants::Window::Width);
		break;
	}
	}
	std::cout << "event" << std::endl;
}

bool InputManager::KeyPress(int key) {
	return this->keyState[key] && this->keyUpdate[key] == this->updateCounter;
}

bool InputManager::KeyRelease(int key) {
	return !this->keyState[key] && this->keyUpdate[key] == this->updateCounter;
}

bool InputManager::IsKeyDown(int key) {
	return this->keyState[key];
}

bool InputManager::MousePress(int button) {
	return this->mouseState[button] && this->mouseUpdate[button] == this->updateCounter;
}

bool InputManager::MouseRelease(int button) {
	return !this->mouseState[button] && this->mouseUpdate[button] == this->updateCounter;
}

bool InputManager::IsMouseDown(int button) {
	return this->mouseState[button];
}

Vec2 InputManager::GetMouse(Vec2 relative) {
	return Vec2 {
		static_cast<float>(GetMouseX()) + relative.x,
		static_cast<float>(GetMouseY()) + relative.y
	};
}

int InputManager::GetMouseX() {
	return this->mouseX;
}

int InputManager::GetMouseY() {
	return this->mouseY;
}

bool InputManager::GamepadPress(int button) {
	return false;
}

bool InputManager::GamepadRelease(int button) {
	return false;
}

bool InputManager::IsGamepadDown(int button) {
	return false;
}

bool InputManager::IsPopRequested() {
	return InputManager::GetInstance().KeyPress(Constants::Key::Escape);
}

bool InputManager::QuitRequested() {
	return this->quitRequested;
}

bool InputManager::IsQuitRequested() {
	return InputManager::GetInstance().QuitRequested();
}
