#pragma once

#include <Constants.h>
#include <GameObject.h>
#include <State.h>
#include <Music.h>

#include <string>
#include <memory>

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