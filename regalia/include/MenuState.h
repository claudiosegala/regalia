#pragma once

#include <Constants.h>
#include <GameObject.h>
#include <State.h>
#include <Music.h>

#include <string>
#include <memory>

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