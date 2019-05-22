#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Logger.h>
#include <Constants.h>

#include <string>

class CameraFollower : public Component {
    public:
    
        CameraFollower (GameObject&);

        void Update(float);

        void Render();
        
        bool Is(std::string);
};