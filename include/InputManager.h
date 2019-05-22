#pragma once

#include <Logger.h>
#include <SDL_Include.h>
#include <Util.h>
#include <Vec2.h>

#include <unordered_map>
#include <tuple>

class InputManager {
    public:

        static InputManager& GetInstance();

        void Update();

        bool KeyPress(int);

        bool KeyRelease(int);

        bool IsKeyDown(int);

        bool MousePress(int);

        bool MouseRelease(int);

        bool IsMouseDown(int);

        Vec2 GetMouse(Vec2 relative);

        int GetMouseX();

        int GetMouseY();

        bool QuitRequested();

    private:

        int mouseX;

        int mouseY;

        int updateCounter;

        bool quitRequested;

        bool mouseState[6];

        int mouseUpdate[6];

        std::unordered_map<int, bool> keyState;

        std::unordered_map<int, int> keyUpdate;

        InputManager();

        ~InputManager() = default;

        void Setup();

        void RetrieveMouse();

        void TreatEvent(SDL_Event& event);

};