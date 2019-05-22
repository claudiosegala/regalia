#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Logger.h>
#include <Timer.h>
#include <Vec2.h>
#include <Util.h>

#include <string>
#include <queue>
#include <vector>
#include <memory>

class Alien : public Component {
    public:

        static int alienCount;

        Alien(GameObject&, int);

        ~Alien();

        void Start();

        void Update(float);

        void Render();

        void NotifyCollision(GameObject&);

        bool Is(std::string);

    private:

        static int const life;

        static int const restCoolDown;

        static float const pace;

        static float const spinPace;

        enum class AlienState { 
            MOVING, 
            RESTING,
            NOP
        };

        int hp;

        Vec2 speed;

        Vec2 destination;
        
        Timer restTimer;

        AlienState state;

        std::vector<std::weak_ptr<GameObject>> minions;

        void Rest(float);

        void Move();

        void Shoot(Vec2);

        int GetClosestMinion(Vec2);

};