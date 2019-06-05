#pragma once

#include <State.h>

class Game {
public:
	Game(const std::string& title, int width, int height);

	~Game();

	void Run();

	void Push(State* state);

	static Game* GetInstance();

	State* GetCurrentState();

	SDL_Renderer* GetRenderer() const;

	SDL_Window* GetWindow() const;

	unsigned GetDeltaTime() const;
	
private:
	static Game* instance;

	unsigned dt = 0;

	unsigned frameStart = 0;

	State* storedState = nullptr;

	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;

	std::stack<std::unique_ptr<State>> stateStack;

	void Start();

	void Loop();

	void End();

	void CalculateDeltaTime();

	void Init_SDL() const;

	void Init_IMG() const;

	void Init_MIX() const;

	void Init_TTF() const;

	void Init_WDW(const std::string& title, int width, int height);

	void Init_RDR();
};