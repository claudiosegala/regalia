#pragma once

#include <Util.h>
#include <GameObject.h>
#include <Collision.h>
#include <Component.h>
#include <Vec2.h>
#include <Rect.h>

class Collider : public Component {
    public:

        Rect box;

        Collider (GameObject&, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

        void Update(float);

        void Render();

        bool Is(std::string);

        void SetScale(Vec2);
        
        void SetOffset(Vec2);

    private:

        Vec2 offset;

        Vec2 scale;

};