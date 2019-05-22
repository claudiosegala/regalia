#pragma once

#include <GameObject.h>
#include <State.h>
#include <Music.h>

class MenuState : public State {
    public:

        MenuState();
        
        ~MenuState();
        
        void LoadAssets();
        
        void Update(float);
        
        void Render();
        
        void Start();
        
        void Pause();
        
        void Resume();

    private:

        int option;

        std::weak_ptr<GameObject> cursor;

        Music music;

        GameObject* CreateOption(std::string, Vec2 shift = { 0, 0 });
};