#pragma once

#include <GameObject.h>
#include <Logger.h>
#include <Util.h>

#include <string>

class GameObject;

class Component {
    public:

        Component(GameObject&);

        virtual ~Component();

        virtual void Start();

        virtual void NotifyCollision(GameObject&);

        virtual void Update(float dt) = 0;

        virtual void Render() = 0;

        virtual bool Is(std::string) = 0;

    protected:
    
        GameObject& associated;

};