#pragma once

#include <Util.h>
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

        std::shared_ptr<Text> cursor;

        Music music;

        GameObject* CreateOption(std::string, Vec2 shift = { 0, 0 });
};