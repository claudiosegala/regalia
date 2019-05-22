#pragma once

#include <Component.h>
#include <GameObject.h>

class CameraFollower : public Component {
    public:
    
        CameraFollower (GameObject&);

        void Update(float);

        void Render();
        
        bool Is(std::string);
};