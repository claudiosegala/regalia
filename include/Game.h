#pragma once

#include <InputManager.h>
#include <Logger.h>
#include <SDL_Include.h>
#include <State.h>
#include <Constants.h>

#include <string>
#include <stdexcept>
#include <iostream>
#include <stack>

class Game {
    public:

        static int const windowWidth;

        static int const windowHeight;

        static std::string const windowName;

        Game(const std::string&, int, int);

        ~Game();

        static Game* GetInstance();

        State* GetCurrentState();

        SDL_Renderer* GetRenderer();

        void Run();

        void Push(State*);

        float GetDeltaTime();

    private:

        static Game* instance;

        float dt;

        unsigned int frameStart;

        State* storedState;

        SDL_Window* window;

        SDL_Renderer* renderer;

        std::stack<std::unique_ptr<State>> stateStack;

        void CalculateDeltaTime();

        void Init_SDL();

        void Init_IMG();

        void Init_MIX();

        void Init_TTF();

        void Init_WDW(const std::string&, int, int);

        void Init_RDR();

        void Start();

        void Loop();

        void End();

};