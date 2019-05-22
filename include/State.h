#pragma once

#include <Constants.h>
#include <GameObject.h>

class State {
    public:
        
        State();
        
        virtual ~State();
        
        virtual void LoadAssets() = 0;
        
        virtual void Update (float) = 0;
        
        virtual void Render() = 0;
        
        virtual void Start() = 0;
        
        virtual void Pause() = 0;
        
        virtual void Resume() = 0;

        virtual bool HasComponent(std::string);

        virtual std::weak_ptr<GameObject> AddObject (GameObject*);
        
        virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject*);
        
        bool PopRequested();

        bool QuitRequested();
        
    protected:

        bool started;

        bool quitRequested;

        bool popRequested;

        virtual void RenderArray();

        void StartArray();

        virtual void UpdateArray(float);

        void PruneArray();

        std::vector<std::shared_ptr<GameObject>> objectArray;
};