#pragma once

#include <Util.h>
#include <Component.h>
#include <GameObject.h>
#include <Vec2.h>

class Minion : public Component {
    public:

        Minion (GameObject&, std::weak_ptr<GameObject>, float arcOffsetDeg = 0);
        
        void Update(float);
        
        void Render();
        
        bool Is(std::string);
        
        void Shoot(Vec2);

    private:

        static float const alienDistance;

        float arc;

        std::weak_ptr<GameObject> alienCenter;

        void SetPosition(float);
};