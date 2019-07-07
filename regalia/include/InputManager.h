#pragma once
#include <pch.h>
#include <Vec2.h>
#include <Gamepad.h>

class InputManager {
public:
	static InputManager& GetInstance();

	void Update();

	bool KeyPress(int key);

	bool KeyRelease(int key);

	bool IsKeyDown(int key);

	bool MousePress(int button);

	bool MouseRelease(int button);

	bool IsMouseDown(int button);

	Vec2 GetMouse(Vec2 relative) const;

	int GetMouseX() const;

	int GetMouseY() const;

	bool GamepadPress(SDL_GameControllerButton button);

	bool GamepadPress(SDL_GameControllerButton button, int controllerNumber);

	bool GamepadRelease(SDL_GameControllerButton button);

	bool GamepadRelease(SDL_GameControllerButton button, int controllerNumber);

	bool IsGamepadDown(SDL_GameControllerButton button);

	bool IsGamepadDown(SDL_GameControllerButton button, int controllerNumber);

	Vec2 GamepadLeftStick(int controllerNumber);

	Vec2 GamepadRightStick(int controllerNumber);

	void GamepadRumble(int controllerNumber, float intensity, unsigned int duration);

	bool PopRequested();

	bool QuitRequested() const;

	int NumberOfControllers() const;

private:
	int mouseX = 0;

	int mouseY = 0;

	int updateCounter = 0;

	bool quitRequested = false;

	bool mouseState[6] = { false };

	int mouseUpdate[6] = { false };

	std::unordered_map<int, bool> keyState;

	std::unordered_map<int, int> keyUpdate;

	std::vector<Gamepad> controllers;

	InputManager();

	~InputManager() = default;

	void Setup();

	void RetrieveMouse();

	void TreatEvent(SDL_Event& event);

	void LoadControllers();

};
