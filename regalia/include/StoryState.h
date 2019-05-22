#pragma once

#include <State.h>
#include <Music.h>

class StoryState : public State {
    public:

        StoryState();
        
        ~StoryState();
        
        void LoadAssets();
        
        void Update(float);
        
        void Render();
        
        void Start();
        
        void Pause();
        
        void Resume();

    private:

        Music music;
};