#pragma once

#include <State.h>
#include <Timer.h>
#include <Music.h>

class PlayState : public State {
    public:

        PlayState();
        
        ~PlayState();
        
        void LoadAssets();
        
        void Update(float);
        
        void Render();
        
        void Start();
        
        void Pause();
        
        void Resume();

    private:

        Timer roundTimer;

        Music music;
};