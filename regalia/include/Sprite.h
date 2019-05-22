#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Logger.h>
#include <SDL_Include.h>
#include <Constants.h>
#include <Timer.h>

#include <string>
#include <iostream>

class Sprite : public Component {
    public:

        Sprite(GameObject&, const std::string&, int frameCount = 1, float frameTime = 1.0f, float secondsToSelfDestruct = 0);

        ~Sprite();

        void Open (const std::string&);

        void SetClip (int, int, int, int);

        void SetClip ();

        void SetBox ();

        void SetScale (float, float);

        Vec2 GetScale();

        void SetFrame(int);

        void SetFrameCount(int);

        void SetFrameTime(float);

        void Update(float);

        void Render();

        void Render(int, int);

        void Render(float, float);

        bool Is(std::string);

        int GetWidth();

        int GetHeight();

        bool IsOpen();

    private:

        int width;

        int height;

        Vec2 scale;

        int frameCount;

        int currentFrame;

        float timeElapsed;

        float frameTime;

        float secondsToSelfDestruct;

        Timer selfDestructCount;

        std::shared_ptr<SDL_Texture> texture;

        SDL_Rect clipRect;

};