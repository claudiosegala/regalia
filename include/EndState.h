#pragma once

#include <Util.h>
#include <State.h>
#include <GameObject.h>
#include <Component.h>
#include <Music.h>

class EndState : public State {
    public:

        EndState();

        ~EndState();

        void LoadAssets();

        void Update(float);

        void Render();

        void Start();

        void Pause();

        void Resume();

    private:

        Music backgroundMusic;
};