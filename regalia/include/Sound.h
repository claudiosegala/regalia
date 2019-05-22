#pragma once

#include <Component.h>
#include <GameObject.h>

class Sound : public Component {
    public:

        Sound(GameObject&);

        Sound(GameObject&, std::string);

        ~Sound();

        void Play(int times = 1);

        void Stop();

        void Open(std::string);

        bool IsOpen();

        void Update(float);

        void Render();

        bool Is(std::string);
    
    private:

        int channel;

        std::shared_ptr<Mix_Chunk> chunk;

};