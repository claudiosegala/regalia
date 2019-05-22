#pragma once

#include <Constants.h>
#include <GameObject.h>
#include <State.h>
#include <Music.h>

#include <string>

class CreditState : public State {
    public:

        CreditState();
        
        ~CreditState();
        
        void LoadAssets();
        
        void Update(float);
        
        void Render();
        
        void Start();
        
        void Pause();
        
        void Resume();

    private:

        Music music;
};