#pragma once

#include <Util.h>
#include <Component.h>
#include <GameObject.h>
#include <Timer.h>

class PenguinCannon : public Component {
    public:

        PenguinCannon(GameObject&, std::weak_ptr<GameObject>);

        void Update(float);

        void Render();

        bool Is(std::string);

        void Shoot();

    private:

        static float const restCoolDown;

        float angle;

        Timer coolDownTime;

        std::weak_ptr<GameObject> pbody;

};